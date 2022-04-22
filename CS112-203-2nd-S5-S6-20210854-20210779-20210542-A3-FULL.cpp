// FCAI - Programming 1 - 2022 - Assignment 3
// Program Name:         CS112-203-2nd-S5-S6-20210854-20210779-20210542-A3-FULL.cpp
// Last modification date: 19/4/2022
// Author1 and ID and Group: Ethar Raid, 20210854, Group A
// Author2 and ID and Group: Youssef Ezat, 20210542, Group A
// Author3 and ID and Group: Malek Yehia, 20210779, Group A
// Teaching Assistant: Hagar Ali
// Purpose: User chooses between 12 filters to apply to 256x256 pictures

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"


using namespace std;
unsigned char img[SIZE][SIZE];
unsigned char quarter[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char outimage[SIZE][SIZE];
static unsigned char Newimage[SIZE][SIZE];
unsigned char L_img[SIZE][128];
unsigned char U_img[128][SIZE];
unsigned char shuffled[SIZE][SIZE];


void loadImage() {
   char imageFileName[100];
   cout << "Please enter file name of the image to process: ";
   cin >> imageFileName;
   cout << endl;
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, img);
}



void black_and_white(){
    double avg;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            {
                avg += img[i][j];
            }
    }
    avg /= (SIZE * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (img[i][j] > avg)
            img[i][j] = 255;
            else
                img[i][j] = 0;
        }
    }
}

void invert(){
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
        if (img[i][j] > 245)
            img[i][j] = 0;
        else
            img[i][j] = 255- img[i][j];
    }
  }
}

void Merge() {
   char imageFileName[100];
   cout << "Please enter file name of the image you want to merge with: ";
   cin >> imageFileName;
   cout << endl;
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image2);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			img[i][j] = (img[i][j] / 2) + (image2[i][j] / 2);
		}
	}
}

void horizontal_flip(unsigned char img[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            swap(img[i][j], img[i][k]);
            j++;
            k--;
        }
    }
}

void vertical_flip(unsigned char img[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            swap(img[j][i], img[k][i]);
            j++;
            k--;
        }
    }
}

void Rotate(){
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            swap(img[i][j], img[i][k]);
            j++;
            k--;
        }
    }

    for (int i = 0; i < SIZE; i++)
        for (int j = i; j < SIZE; j++)
            swap(img [i][j], img [j][i]);
}

void Rotate180()
{
    Rotate();
    Rotate();
}

void Rotate270()
{
    Rotate();
    Rotate();
    Rotate();
}

void darken_and_lighten() {

    double avg;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            {
                avg += img[i][j];
            }
    }
    avg /= (SIZE * SIZE);

    char light;
    cout <<"Do you want to (d)arken or (l)ighten?: ";
    cin >> light ;
    if (light == 'l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                    if (img [i][j]>64)
                        img [i][j]=255;
                    else
                        img [i][j]=0;
            }
        }
    }

    else if (light == 'd'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                    img [i][j] = img[i][j]/4;
            }
    }

  }
     else
        cout <<"invalid input\n";
}

void detect_edges() {
   int x_val[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
   int y_val[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

   double gx, gy;
   int i_index = 0;
   int j_index = 0;
   int pixel_val;

   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
            gx = 0;
            gy = 0;
            for (int x = 0; x < 3; x++) {
                for (int y = 0 ; y < 3; y++){

                    i_index = (i - 1) + x;
                    j_index = (j - 1) + y;

                    if (0 <= i_index && i_index <=255 && 0 <= j_index && j_index <= 255){
                        gx += img[i_index][j_index] * x_val[x][y];
                        gy += img[i_index][j_index] * y_val[x][y];
                    }
                }
            }

            pixel_val = round (sqrt((gx * gx) + (gy * gy)));
            if (pixel_val > 255) {
                pixel_val= 255;
            }
            Newimage[i][j] = (255 - pixel_val > 127) ? 255:0;
            //Newimage[i][j] = (255 - pixel_val );

      }
   }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        img[i][j] = Newimage[i][j];
}

void enlarge_q1(){
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            quarter [i][j] = img [i/2][j/2];
        }
    }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        img [i][j] = quarter [i][j];
}

void enlarge_q2(){
    horizontal_flip(img);
    enlarge_q1();
    horizontal_flip(img);
}

void enlarge_q3(){
    vertical_flip(img);
    enlarge_q1();
    vertical_flip(img);
}

void enlarge_q4(){
    horizontal_flip(img);
    vertical_flip(img);

    enlarge_q1();

    horizontal_flip(img);
    vertical_flip(img);
}

void shrink(){
    //Shrinking variable
    string number;
    int Wtrue;
    Wtrue = true;
    while (Wtrue) {
            // ask the user if he want 1/4 or 1/3 or 1/2
        cout << "press \" 4 \" for 1/4... press \" 3 \" for 1/3...press \"2\" for 1/2: ";
        cin >> number;
        if (number == "2" || number == "3" || number == "4"){
            // break (while loop) and go on to the (for loop)
            break;
        }

        else {
                // if taking a valid input
            cout << "enter a valid input ! " << endl;
        }
    }
    for (int i = 0; i < SIZE; i+=2) {
        for (int j = 0; j< SIZE; j+=2) {

            if (number == "2"){
                // divide i,j by 2 for making the photo to half its real
                outimage[i/2][j/2] = img[i][j];
            }
            else if (number == "3"){
                // divide i,j by 3 for making the photo to third its real
                outimage[i/3][j/3] = img[i][j];
            }
            else if (number == "4"){
                // divide i,j by 4 for making the photo to quarter its real
                outimage[i/4][j/4] = img[i][j];
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        img[i][j] = outimage[i][j];
}

void h_flip(unsigned char m_img[SIZE][128]){
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            swap(img[i][j], img[i][k]);
            j++;
            k--;
        }
    }
}

void v_flip(unsigned char U_img[128][SIZE]){
    for (int i = 0; i < SIZE; i++)
    {
        int j = 0;
        int k = SIZE - 1;
        while (j < k)
        {
            swap(img[j][i], img[k][i]);
            j++;
            k--;
        }
    }
}

void mirror(){
    char direction;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?: ";
    cin >> direction;
    if (direction == 'l')
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE/2; j++)
            L_img[i][j] = img[i][j];

        h_flip(L_img);
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < 128; j++)
            swap (L_img[i][j], img[i][j]);
    }
    if (direction == 'r')
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE; j > SIZE/2; j--)
            L_img[i][j] = img[i][j];

        h_flip(L_img);
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE; j > 128; j--)
            swap (L_img[i][j], img[i][j]);
    }
    if (direction == 'u')
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE/2; j++)
            U_img[j][i] = img[j][i];

        v_flip(U_img);
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < 128; j++)
            swap (U_img[j][i], img[j][i]);
    }
    if (direction == 'd')
    {
        Rotate();
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE; j > SIZE/2; j--)
            L_img[i][j] = img[i][j];

        h_flip(L_img);
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE; j > 128; j--)
            swap (L_img[i][j], img[i][j]);
        Rotate();
    }
}

void shuffle()
{
    string order;
    cout << "New order of the first quarter?: ";
    cin >> order;
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j < SIZE/2; j++)
        {
            int row1;
            int column1;
            for (char m: order)
            {

                if (m == '1'){
                    row1 = i;
                    column1 = j;
                }
                else if (m == '2'){
                    row1 = i;
                    column1 = j+128;
                }
                else if (m == '3'){
                    row1 = i+128;
                    column1 = j;
                }
                else if (m == '3'){
                    row1 = i+128;
                    column1 = j;
                }
                else if (m == '4'){
                    row1 = i+128;
                    column1 = j+128;
                }
            }
            shuffled[i][j] += img[row1][column1];
        }
    }

    string order2;
    cout << "New order of the second quarter?: ";
    cin >> order2;
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j < SIZE/2; j++)
        {
            int row2;
            int column2;
            for (char m: order2)
            {
                if (m == '1'){
                    row2 = i;
                    column2 = j;
                }
                else if (m == '2'){
                    row2 = i;
                    column2 = j+128;
                }
                else if (m == '3'){
                    row2 = i+128;
                    column2 = j;
                }
                else if (m == '3'){
                    row2 = i+128;
                    column2 = j;
                }
                else if (m == '4'){
                    row2 = i+128;
                    column2 = j+128;
                }
            }
            shuffled[i][j+128] += img[row2][column2];
        }
    }

    string order3;
    cout << "New order of the third quarter?: ";
    cin >> order3;
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j < SIZE/2; j++)
        {
            int row3;
            int column3;
            for (char m: order3)
            {
                if (m == '1'){
                    row3 = i;
                    column3 = j;
                }
                else if (m == '2'){
                    row3 = i;
                    column3 = j+128;
                }
                else if (m == '3'){
                    row3 = i+128;
                    column3 = j;
                }
                else if (m == '3'){
                    row3 = i+128;
                    column3 = j;
                }
                else if (m == '4'){
                    row3 = i+128;
                    column3 = j+128;
                }
            }
            shuffled[i+128][j] += img[row3][column3];
        }
    }

    string order4;
    cout << "New order of the fourth quarter?: ";
    cin >> order4;
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j < SIZE/2; j++)
        {
            int row4;
            int column4;
            for (char m: order4)
            {
                if (m == '1'){
                    row4 = i;
                    column4 = j;
                }
                else if (m == '2'){
                    row4 = i;
                    column4 = j+128;
                }
                else if (m == '3'){
                    row4 = i+128;
                    column4 = j;
                }
                else if (m == '3'){
                    row4 = i+128;
                    column4 = j;
                }
                else if (m == '4'){
                    row4 = i+128;
                    column4 = j+128;
                }
            }
            shuffled[i+128][j+128] += img[row4][column4];
        }
    }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        img[i][j] = shuffled[i][j];
}

// function for blur
void blur () {
    int average = 0;
    for (int i=0 ; i < SIZE ; i++){
        for (int j=0 ; j < SIZE ; j++){
            for (int k = -1; k <= 1; k ++){
                for (int l = -1; l <= 1 ;l++){
                    // if condition for not making some edges black
                    if((i + k) >= 0 && (i + k) <= 255 && (j + l) >= 0 && (j + l) <= 255){
                        average += img[i + k][j + l];
                    }
                }
            }
            outimage[i][j] = (average / 9);
            // making average = 0 again
            average = 0;
        }
    }

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        img[i][j] = outimage[i][j];
}

void saveImage() {
   char imageFileName[100];
   cout << "Enter the target image file name: ";
   cin >> imageFileName;
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, img);
}


int main()
{
    loadImage();
    static char user;
    while (true){
                cout << "\n1- Black & White Filter\n" << "2- Invert Filter\n" << "3- Merge Filter\n" << "4- Flip Image\n";
                cout << "5- Rotate Image\n" << "   x- Rotate 180 Degrees\n" << "   y- Rotate 270 Degrees\n";
                cout << "6- Darken and Lighten Image\n" << "7- Detect Image Edges\n" << "8- Enlarge Image\n";
                cout << "9- Shrink Image\n" << "a- Mirror 1/2 Image\n" << "b- Shuffle Image\n" << "c- Blur Image\n";
                cout << "s- Save the image to a file\n" << "0- Exit\n" << "Please select a filter to apply or 0 to exit and save: ";
                cin >> user;
                if (user == '0'){
                    saveImage();
                    return false;
                }
                else if (user == '1'){
                    black_and_white();
                }
                else if (user == '2'){
                    invert();
                }
                else if (user == '3'){
                    Merge();
                }
                else if (user == '4'){
                    char h_v;
                    cout << "Flip (h)orizontally or (v)ertically ?: ";
                    cin >> h_v;
                    if (h_v == 'h')
                        horizontal_flip(img);
                    if (h_v == 'v')
                        vertical_flip(img);
                }
                else if (user == '5'){
                    Rotate();
                }
                else if (user == 'x'){
                    Rotate180();
                }
                else if (user == 'y'){
                    Rotate270();
                }
                else if (user == '6'){
                    darken_and_lighten();
                }
                else if (user == '7'){
                    detect_edges();
                }
                else if (user == '8'){
                    char qrtr;
                    cout << "Which quarter to enlarge 1, 2, 3 or 4?: ";
                    cin >> qrtr;
                    if (qrtr == '1')
                        enlarge_q1();
                    if (qrtr == '2')
                        enlarge_q2();
                    if (qrtr == '3')
                        enlarge_q3();
                  if (qrtr == '4')
                        enlarge_q4();
                }
                else if (user == '9'){
                    shrink();
                }
                else if (user == 'a'){
                    mirror();
                }
                else if (user == 'b'){
                    shuffle();
                }
                else if (user == 'c'){
                    blur();
                    blur();
                    blur();
                }
                else if (user == 's'){
                    saveImage();
                }
                else{
                    cout<< "Invalid input" << endl;
                    continue;
                }

    }
    return 0;
}
