import processing.net.*; 
Client myClient;
int dataIn; 
byte[] byteBuffer = new byte[10];
String buffer = "Got it";
byte[] ImageArray = new byte[30241];
int read_size = 0;
int packageIndex = 0;
int imageSize = 0;
PImage photo;
OutputStream output1;
void setup() {
  size(640, 480);
  // Connect to the local machine at port 5204.
  // This example will not run if you haven't
  // previously started a server on this port.
  myClient = new Client(this, "10.0.0.7", 8000);
 
  output1 = createOutput("imagen.jpg");
  frameRate(200);
}

int byteArrayToInt(byte[] b) 
{
    return   b[0] & 0xFF |
            (b[1] & 0xFF) << 8 |
            (b[2] & 0xFF) << 16 |
            (b[3] & 0xFF) << 24;
}

void draw() {
  if (myClient.available() > 0) 
  {
    int size = myClient.readBytes(byteBuffer); 
    imageSize = byteArrayToInt(byteBuffer);
    println("Package recived");
    println("Packet size: " + size);
    println("Image size: " + imageSize);
    delay(10);
    myClient.write(buffer);
    myClient.clear();
    println("Reply sent");
    output1 = createOutput("imagen.jpg");
    while (read_size < imageSize)
    {
      try
      {
        while ( myClient.available() > 0)
        {
          int totalBytes = myClient.readBytes(ImageArray);
          byte[] tmpBuffer= new byte[totalBytes]; 
          arrayCopy(ImageArray,tmpBuffer,totalBytes);
          output1.write(tmpBuffer);
          read_size+=totalBytes;
        }
      }
      catch (IOException e) 
      {
        e.printStackTrace();
      }
    }
     println("Total received image size: " + read_size);
     read_size = 0;
     myClient.write("finish capture");
     myClient.clear();
     try 
     { 
      output1.flush();  // Writes the remaining data to the file
      output1.close();  // Finishes the file
      photo = loadImage("imagen.jpg");
      image(photo, 0, 0);
    } 
  
    catch (IOException e) 
    {
      e.printStackTrace();
    }
  //  
    }
   // background(51);
    
    
    
    
}