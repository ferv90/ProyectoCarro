#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <sys/poll.h>
#include <objdetect/objdetect.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define SEND_DATA 	1
#define RECIVE_DATA 0
void DetectObjects( Mat frame );
void WaitToTrasnfer(int socket,int Status);
std::mutex mtxCam;
String Object_cascade_name = "haarcascade_frontalface_alt.xml";
CascadeClassifier Object_cascade;


int uart0_filestream = -1;

void task(VideoCapture *cap, Mat *frame)
    {
        while (true)
        {
            mtxCam.lock();
            if( cap->read(*frame) != 1){
            	puts(" Error capture");
            	continue;
            }
            mtxCam.unlock();
            waitKey(1);
        }
    }

void WaitToTrasnfer(int socket,int Status)
{
	struct pollfd ufds[1];
    ufds[0].fd = socket;
    int rv;
    static const int TIME_OUT = 3000;
	switch(Status)
	{
	case SEND_DATA:
		ufds[0].events = POLLOUT;
		rv = poll(ufds,1,TIME_OUT);
		break;

	case RECIVE_DATA:
		ufds[0].events = POLLIN | POLLPRI;
		rv = poll(ufds,1,TIME_OUT);
		break;
	}
	if(rv == -1)
	{
		perror("error in poll");
	}else if(rv == 0)
	{
		printf("Timeout occurred!  No data after %d seconds.\n",TIME_OUT/1000);
	}
}
int send_image(int socket, char * Image_path){

    FILE *picture;
    int size, read_size, stat, packet_index;
    char read_buffer[256];

    packet_index = 1;


    picture = fopen(Image_path, "r");
    printf("Getting Picture Size\n");

    if(picture == NULL) {
        printf("Error Opening Image File");
    }

    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    printf("Total Picture size: %i\n",size);

    //Send Picture Size
    printf("Sending Picture Size\n");
    WaitToTrasnfer(socket,SEND_DATA);
    write(socket, (void *)&size, sizeof(int));

    //Send Picture as Byte Array
    printf("Sending Picture as Byte Array\n");

    do { //Read while we get errors that are due to signals.
    	WaitToTrasnfer(socket,RECIVE_DATA);
        stat=read(socket, &read_buffer , 255);
        printf("Bytes read: %i\n",stat);
    } while (stat < 0);

    printf("Received data in socket\n");
    printf("Socket data: %s\n", read_buffer);
    char send_buffer[size];
    while(!feof(picture))
    {
        //while(packet_index = 1){
        //Read from the file into our send buffer
        read_size = fread(send_buffer, 1, sizeof(send_buffer)-1, picture);

        //Send data through our socket
        do
        {
        	WaitToTrasnfer(socket,SEND_DATA);
            stat = write(socket, send_buffer, read_size);
        }while (stat < 0);

        printf("Packet Number: %i\n",packet_index);
        printf("Packet Size Sent: %i\n",read_size);
        printf(" \n");
        printf(" \n");

        packet_index++;

        //Zero out our send buffer
        bzero(send_buffer, sizeof(send_buffer));

    }
    stat = 0;
    bzero(read_buffer, sizeof(read_buffer));
    do { //Read while we get errors that are due to signals.
    	WaitToTrasnfer(socket,RECIVE_DATA);
        stat=read(socket, &read_buffer , 255);
        printf("Bytes read: %i\n",stat);
    } while (stat < 0);

    printf("Received data in socket\n");
    printf("Socket data: %s\n", read_buffer);
    return 1;
}

int InitTCP(void){
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket\n");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8000 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }

    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    if((new_socket = accept(socket_desc, (struct sockaddr *)&client,       (socklen_t*)&c))){
        puts("Connection accepted");
     }

     fflush(stdout);
     return new_socket;
}

void DetectObjects(Mat frame ){
	std::vector<Rect> Objetcs;
	Mat frame_gray;
	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );


	//-- Detect faces
	//todo: Object_cascade.detectMultiScale( frame_gray, Objetcs, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	 for( size_t i = 0; i < Objetcs.size(); i++ )
	  {
		 Point center( Objetcs[i].x + Objetcs[i].width*0.5, Objetcs[i].y + Objetcs[i].height*0.5 );
		 ellipse( frame, center, Size( Objetcs[i].width*0.5, Objetcs[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	  }


}

int main(void)
{
    int socketValue;
    char ImagePath[] = "imagen.jpg";
    Mat save_img;
    Mat Image;
    VideoCapture cap(0); // open the video camera no. 0

    cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    std::vector<int> params;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(20);   // that's percent, so 100 == no compression, 1 == full

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }
    socketValue =InitTCP();
   /* if( !Object_cascade.load( Object_cascade_name ) )
    {
    	printf("--(!)Error loading\n");
    	return -1;
    }*/

    cap.read(save_img);
    thread t(task, &cap, &save_img);
    while(1){

		 mtxCam.lock();
		 save_img.copyTo(Image);
		 imwrite(ImagePath, Image,params); // A JPG FILE IS BEING SAVED
		 mtxCam.unlock();
		// Save the frame into a file


		send_image(socketValue,ImagePath);
		waitKey(1000);

    }
    close(socketValue);
    fflush(stdout);
    return 0;

}
