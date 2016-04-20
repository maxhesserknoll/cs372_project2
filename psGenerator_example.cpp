
#include "psGenerator.h"
#include<iostream>
#include <fstream>
//test basic shapes
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

int main()
{
    
	ofstream myfile;
	myfile.open("psExampleOuput.ps");
	myfile << "%! \n";
	myfile << "%PS file generated using a postscript generator \n";
	myfile << "%Created by Jesse Zhang, Max Hesser-Knoll, James Lang, Scott Corcoran \n";

    // Example of basic shapes with decorators
    Circle testCirc(50);
    Scaled testEllipse(&testCirc, 3, 1);
    Rotate testRotateEllipse(&testEllipse, 90);
    Layered testLayered = {&testCirc, &testEllipse, &testRotateEllipse};
    
    myfile << testLayered.toString(150, 150);
    
    
    Scaled scaledLayered(&testLayered, 0.3, 0.1);
    Rotate rotateScaledLayered(&scaledLayered,90);
    Spacer testSpacer(30,20);
    Vertical testVertical = {&scaledLayered, &rotateScaledLayered, &testSpacer, &rotateScaledLayered, &scaledLayered};
    
    myfile << testVertical.toString(432, 72);
    
        
    // Example of custom shapes with decorators
    FiftyShades test50shades(72);
    FiftyShades test50shades2(155);
    Trapezoid testTrapezoid(72, 144, 100);
    Rotate testTrapezoidRotate90(&testTrapezoid, 90);
    Rotate testTrapezoidRotateNeg90(&testTrapezoid, -90);
    
    Horizontal testHorizontal = {&test50shades2, &testTrapezoidRotateNeg90, &testTrapezoidRotate90, &testTrapezoidRotateNeg90, &test50shades};
    
    myfile << testHorizontal.toString(72, 500);

	myfile << "\n";
	myfile << " showpage";


	myfile << "%PS file generated using a postscript generator \n";
	myfile << "%Created by Jesse Zhang, Max Hesser-Knoll, James Lang, Scott Corcoran \n";

	Rectangle head(144,72);

	Rectangle body(200, 72*3);

	Circle lefteye(20);
	Circle righteye(20);
	Polygon lefteyeinside(8,10);
	Polygon righteyeinside(6, 15);

	Trapezoid mouth(10,24,8);
	Rectangle mouthline1(10, 10);
	Rectangle mouthline2(3.5, 10);

	Rectangle leftleg(88, 72);
	Rectangle rightleg(88, 72);
	Rectangle leftlegband1(88, 22);
	Rectangle rightlegband1(88, 22);
	Rectangle leftlegband2(88, 48);
	Rectangle rightlegband2(88, 48);

	Rectangle rightarm(25, 140);
	Rectangle leftarm(25,140);

	Triangle leftsholder(36);
	Triangle rightsholder(36);

	
	Rectangle antena(4,28);
	Circle antenaBall(10);
	myfile << head.toString((72*3),(72*7)) << endl;
	myfile << antena.toString(72*3 - 36,72*7 + 50) << endl;
	myfile << antenaBall.toString(72*3 - 36,72*8 +2) << endl;

	myfile << body.toString((72 * 3), (72 * 5)) << endl;
	Square plate(72);
	myfile << plate.toString(72*4 - 8, 72*5 +10) << endl;

	Polygon bolt(6,4);
	myfile << bolt.toString(72 * 4 + 17, 72 * 5 + 40) << endl;
	myfile << bolt.toString(72 * 4 - 5, 72 * 5 + 40) << endl;
	myfile << bolt.toString(72 * 4 - 34, 72 * 5 + 40) << endl;
	myfile << bolt.toString(72 * 4 - 34, 72 * 5 + 10) << endl;
	myfile << bolt.toString(72 * 4 - 34, 72 * 5 + -20) << endl;
	myfile << bolt.toString(72 * 4 - 8, 72 * 5 - 20) << endl;
	myfile << bolt.toString(72 * 4 + 17, 72 * 5 - 20) << endl;
	
	//Second set of bolts and plate
	Square plate1(72);
	myfile << plate1.toString(72 * 2 + 8, 72 * 4 ) << endl;
	myfile << bolt.toString(72 * 2 + 36, 72 * 4 - 28) << endl;
	myfile << bolt.toString(72 * 2 + 10, 72 * 4 - 28) << endl;
	myfile << bolt.toString(72 * 2 - 16, 72 * 4 - 28) << endl;
	myfile << bolt.toString(72 * 2 + 36, 72 * 4 + 28) << endl;
	myfile << bolt.toString(72 * 2 + 36, 72 * 4 ) << endl;
	myfile << bolt.toString(72 * 2 - 16, 72 * 4 + 28) << endl;
	myfile << bolt.toString(72 * 2 + 10, 72 * 4 + 28) << endl;



	myfile << lefteye.toString((72 * 3)-20, (72 * 7)) << endl;
	myfile << righteye.toString((72 * 3)+20, (72 * 7)) << endl;
	myfile << lefteyeinside.toString((72 * 3) - 20, (72 * 7)) << endl;
	myfile << righteyeinside.toString((72 * 3) + 20, (72 * 7)) << endl;

	myfile << mouth.toString((72 * 3), (72 * 7)-24) << endl;
	myfile << mouthline1.toString((72 * 3), (72 * 7) - 24) << endl;
	myfile << mouthline2.toString((72 * 3), (72 * 7) - 24) << endl;

	myfile << leftleg.toString((72 * 2.25), (72 * 3)) << endl;
	myfile << rightleg.toString((72 * 3.75), (72 * 3)) << endl;
	myfile << leftlegband1.toString((72 * 2.25), (72 * 3)) << endl;
	myfile << rightlegband1.toString((72 * 3.75), (72 * 3)) << endl;
	myfile << leftlegband2.toString((72 * 2.25), (72 * 3)) << endl;
	myfile << rightlegband2.toString((72 * 3.75), (72 * 3)) << endl;

	Rotate rotateleftsholder(&leftsholder,90);
	Rotate rotaterightsholder(&rightsholder, 270);
	myfile << rotateleftsholder.toString(72*1.45, 72 * 6 +30) << endl;
	myfile << rotaterightsholder.toString(72*4.55, 72 * 6 +30) << endl;
	myfile << rightarm.toString((72 * 4.61), (72 * 5.5)) << endl;
	myfile << leftarm.toString((72 * 1.39), (72 * 5.5)) << endl;


	Triangle righthand(22);
	Triangle lefthand(22);
	Rotate rotatelefthand(&lefthand, 180);
	Rotate rotaterighthand(&righthand, 180);
	myfile << rotaterighthand.toString((72 * 4.61), (72 * 4.48) - 2) << endl;
	myfile << rotatelefthand.toString((72 * 1.39), (72 * 4.48) - 2) << endl;
	Triangle rightfinger1(22);
	Triangle leftfinger1(22);
	Rotate rotateleftfinger1(&leftfinger1, 180);
	Rotate rotaterightfinger1(&rightfinger1, 180);
	myfile << rotaterightfinger1.toString((72 * 4.66), (72 * 4.44) - 8) << endl;
	myfile << rotateleftfinger1.toString((72 * 4.56), (72 * 4.44) - 8) << endl;
	Triangle rightfinger2(22);
	Triangle leftfinger2(22);
	Rotate rotateleftfinger2(&leftfinger2, 180);
	Rotate rotaterightfinger2(&rightfinger2, 180);
	myfile << rotaterightfinger2.toString((72 * 1.44), (72 * 4.44) - 8) << endl;
	myfile << rotateleftfinger2.toString((72 * 1.34), (72 * 4.44) - 8) << endl;


	myfile << "\n";
	myfile << " showpage";

	myfile.close();
	return 0;
}