import gab.opencv.*;
import SimpleOpenNI.*;
import KinectProjectorToolkit.*;

import org.opencv.imgproc.Imgproc;
import org.opencv.core.*;


// import UDP library
import hypermedia.net.*;


UDP udp;  // the UDP object


SimpleOpenNI kinect;
OpenCV opencv;
KinectProjectorToolkit kpc;
ArrayList<ProjectedContour> projectedContours;
ArrayList<PGraphics> projectedGraphics;

void setup()
{
  //size(displayWidth, displayHeight, P2D);
 size (1280,720,P2D);


  // setup UDP
  // create a multicast connection on port 6000
  // and join the group at the address "224.0.0.1"
  udp = new UDP( this, 11999, "224.0.0.1" );
  // wait constantly for incomming data
  udp.listen( true );
  // ... well, just verifies if it's really a multicast socket and blablabla
  println( "init as multicast socket ... "+udp.isMulticast() );
  println( "joins a multicast group  ... "+udp.isJoined() );
 

  // setup Kinect
  kinect = new SimpleOpenNI(this); 
  kinect.enableDepth();
  kinect.enableUser();
  kinect.alternativeViewPointDepthToImage();
  
  // setup OpenCV
  opencv = new OpenCV(this, kinect.depthWidth(), kinect.depthHeight());

  // setup Kinect Projector Toolkit
  kpc = new KinectProjectorToolkit(this, kinect.depthWidth(), kinect.depthHeight());
  kpc.loadCalibration("calibration.txt");
  kpc.setContourSmoothness(4);
  
  projectedGraphics = initializeProjectedGraphics();
}

 
String packVector(PVector p, PVector t) {
  return p.x + "," + p.y + "|" + t.x + "," + t.y;
}

String packVector(ArrayList<PVector> v) {
  System.out.println("packVector passed " + v.size() + " vectors");
  String p = "";
  for (PVector i : v) {
    p += i.x + "," + i.y + "|";
  }
  System.out.println ("got p " + p);
  if (p!="") p = p.substring(0,p.length()-1);

  System.out.println("packed arraylist: " + p);
  return p;
}

void sendHex(ProjectedContour contour) {
    //MatOfPoint2f approx = new MatOfPoint2f();
    //Imgproc.approxPolyDP(new MatOfPoint2f(contour.toArray()), approx)); //, epsilon, true);
    
    //contour = Imgproc.convexHull(new MatOfPoint(contour.toArray()));
    //contour = contour.getPolygonApproximation();
    
    udp.send(packVector(contour.getProjectedContours())+"[/p]"); //getProjectedContours()));      
  
}

void sendBounds(ProjectedContour contour) {
  java.awt.Rectangle bounds = contour.getBoundingBox();
  String packed = packVector(new PVector(bounds.x,bounds.y), new PVector(bounds.width,bounds.height)); 
  System.out.println ("packed " + packed);
  udp.send(packed); //unds,bounds));
}
  
void sendContour(ProjectedContour contour) {
  String packed = ""; 
  for (PVector p : contour.getProjectedContours()) { 
      PVector t = contour.getTextureCoordinate(p);
      packed += packVector(p,t);
      //packed += packVector(t);
      
      /*packed += //"[ " + 
        //t.x + "|" + t.y
        p.x + "|" + p.y + "|" + t.x + "|" + t.y
        //+ " ]"; //t.z + "]"
      ;*/
      packed += "[/p]";
  }  
  System.out.println("packed: " + packed);
  
  udp.send(packed);
}

void draw()
{  
  kinect.update();  
  kpc.setDepthMapRealWorld(kinect.depthMapRealWorld()); 
  kpc.setKinectUserImage(kinect.userImage());
  opencv.loadImage(kpc.getImage());
  
  //image(kpc.getImage(),0,0);
  background(0);
  int sentCount = 0;
  
  // get projected contours
  projectedContours = new ArrayList<ProjectedContour>();
  ArrayList<Contour> contours = opencv.findContours();
  for (Contour contour : contours) {
    if (contour.area() > 2000) {
      //System.out.println(contour);
      //contour = Imgproc.convexHull(new MatOfPoint(contour),newMatofInt());
      ArrayList<PVector> cvContour = contour.getPoints();
      ProjectedContour projectedContour = kpc.getProjectedContour(cvContour, 1.0); //0.1); //1.0); //0.5); //1.0);
      projectedContours.add(projectedContour);
      //System.out.println(projectedContour);
      //sendContour(projectedContour);
      if (sentCount==0) {
        //sendBounds(projectedContour);
        sendHex(projectedContour);
        java.awt.Rectangle bb = projectedContour.getBoundingBox();
        rect(bb.x, bb.y, bb.width, bb.height);
      }
      sentCount++;
    }
  }
  System.out.println("this frame, sent " + sentCount + " contours");
  
  // draw projected contours
  //background(0);
  for (int i=0; i<projectedContours.size(); i++) {
    ProjectedContour projectedContour = projectedContours.get(i);
    PGraphics pg = projectedGraphics.get(i%3);    
    beginShape();
    texture(pg);
    for (PVector p : projectedContour.getProjectedContours()) {
      PVector t = projectedContour.getTextureCoordinate(p);
      vertex(p.x, p.y, pg.width * t.x, pg.height * t.y);
    }
    endShape();
  }
}

ArrayList<PGraphics> initializeProjectedGraphics() {
  ArrayList<PGraphics> projectedGraphics = new ArrayList<PGraphics>();
  for (int p=0; p<3; p++) {
    color col = color(random(255), random(255), random(255));
    PGraphics pg = createGraphics(800, 400, P2D);
    pg.beginDraw();
    pg.background(random(255));
    pg.noStroke();
    for (int i=0; i<100; i++) {
      pg.fill(red(col)+(int)random(-30,30), green(col)+(int)random(-30,30), blue(col)+(int)random(-30,30)); 
      if      (p==0)  pg.ellipse(random(pg.width), random(pg.height), random(200), random(200));
      else if (p==1)  pg.rect(random(pg.width), random(pg.height), random(200), random(200));
      else if (p==2)  pg.triangle(random(pg.width), random(pg.height), random(pg.width), random(pg.height), random(pg.width), random(pg.height));
    }
    pg.endDraw();
    projectedGraphics.add(pg);
  }  
  return projectedGraphics;
}
