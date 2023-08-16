#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


int min(int a ,int b, int c){
    return a<b ? (a<c?a:c) :(b<c?b:c);
}
int min(int a , int b){
    return a<b ? a : b;
}

void removeHorizontalSeam(int ***rgb,int H, int W, int C){
    // calculation of energy matrix
    int energyMatrix[H][W];
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            int xindex1 = (j+1+W)%W;
            int xindex2 = (j-1+W)%W;
            int dxr=rgb[i][xindex1][0] - rgb[i][xindex2][0];
            int dxg=rgb[i][xindex1][1] - rgb[i][xindex2][1];
            int dxb=rgb[i][xindex1][2] - rgb[i][xindex2][2];
            int yindex1=(i+1+H)%H;
            int yindex2=(i-1+H)%H;
            int dyr=rgb[yindex1][j][0] - rgb[yindex2][j][0];
            int dyg=rgb[yindex1][j][1] - rgb[yindex2][j][1];
            int dyb=rgb[yindex1][j][2] - rgb[yindex2][j][2]; 
            int dx = (dxr*dxr)+(dxg*dxg)+(dxb*dxb);
            int dy = (dyr*dyr)+(dyg*dyg)+(dyb*dyb);
            int val = sqrt(dx+dy);
            energyMatrix[i][j] = val;
        }
    }
    
    int dpMatrix[H][W]; 
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(j==0)
                dpMatrix[i][j]=energyMatrix[i][j];
            else
                dpMatrix[i][j]=0;
        }
    }
    
    for(int j=1;j<W;j++){
        for(int i=0;i<H;i++){
            if(i==0){
                int a = dpMatrix[i][j-1];
                int b = dpMatrix[i+1][j-1];
                dpMatrix[i][j]=energyMatrix[i][j]+min(a,b);
            }else
            if(i==H-1){
                int a = dpMatrix[i-1][j-1];
                int b = dpMatrix[i][j-1];
                dpMatrix[i][j]=energyMatrix[i][j]+min(a,b);  
            }
            else{
                int a = dpMatrix[i-1][j-1];
                int b = dpMatrix[i][j-1];
                int c = dpMatrix[i+1][j-1];
                dpMatrix[i][j]=energyMatrix[i][j]+min(a,b,c);
            }
        }
    }
    
    // finding the minimum cost
    int minSeamVal = dpMatrix[0][W-1];
    int minSeamIndex = 0;
    for(int i=0;i<H;i++){
        if(minSeamVal>dpMatrix[i][W-1]){
            minSeamVal=dpMatrix[i][W-1];
            minSeamIndex=i;
        }
    }
    // removing the minimum seam
    for(int i=W-1;i>=0;i--){
        
        int minIndex;
        if(minSeamIndex==0){
            int b = dpMatrix[minSeamIndex][i-1];
            int c = dpMatrix[minSeamIndex+1][i-1];
            minIndex = b<c ? minSeamIndex : minSeamIndex+1 ;
        }else if(minSeamIndex==H-1){
            int a = dpMatrix[minSeamIndex-1][i-1];
            int b = dpMatrix[minSeamIndex][i-1];
            minIndex = a<b ? minSeamIndex-1 : minSeamIndex ;
        }
        else{
            int a = dpMatrix[minSeamIndex-1][i-1];
            int b = dpMatrix[minSeamIndex][i-1];
            int c = dpMatrix[minSeamIndex+1][i-1];
        
            minIndex = a<b 
                        ? (a<c?minSeamIndex-1:minSeamIndex+1)
                        : (b<c?minSeamIndex:minSeamIndex+1);
        }
        
        for(int j=minSeamIndex;j<H-1;j++){
                rgb[j][i][0]=rgb[j+1][i][0];                                
                rgb[j][i][1]=rgb[j+1][i][1];
                rgb[j][i][2]=rgb[j+1][i][2];
                dpMatrix[j][i]=dpMatrix[j+1][i];
        }
        minSeamIndex=minIndex;
    }  
}

void removeVerticalSeam(int ***rgb,int H, int W, int C){
    // calculation of energy matrix
    
    int energyMatrix[H][W];

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            int xindex1 = (j+1+W)%W;
            int xindex2 = (j-1+W)%W;
            int dxr=rgb[i][xindex1][0] - rgb[i][xindex2][0];
            int dxg=rgb[i][xindex1][1] - rgb[i][xindex2][1];
            int dxb=rgb[i][xindex1][2] - rgb[i][xindex2][2];
            int yindex1=(i+1+H)%H;
            int yindex2=(i-1+H)%H;
            int dyr=rgb[yindex1][j][0] - rgb[yindex2][j][0];
            int dyg=rgb[yindex1][j][1] - rgb[yindex2][j][1];
            int dyb=rgb[yindex1][j][2] - rgb[yindex2][j][2]; 
            int dx = (dxr*dxr)+(dxg*dxg)+(dxb*dxb);
            int dy = (dyr*dyr)+(dyg*dyg)+(dyb*dyb);
            int val = sqrt(dx+dy);
            energyMatrix[i][j] = val;
        }
    }    
    int dpMatrix[H][W];
    
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(i==0){
                dpMatrix[i][j]=energyMatrix[i][j];
            }else
            if(j==0){
                dpMatrix[i][j]=energyMatrix[i][j]+min(
                    dpMatrix[i-1][j],
                    dpMatrix[i-1][j+1]
                    ); 
            }else
            if(j==W-1){
                dpMatrix[i][j]=energyMatrix[i][j]+min(
                    dpMatrix[i-1][j-1],
                    dpMatrix[i-1][j]
                    );
            }
            else{
                dpMatrix[i][j]=energyMatrix[i][j]+min(
                       dpMatrix[i-1][j-1],
                       dpMatrix[i-1][j],
                       dpMatrix[i-1][j+1] ); 
            }   
        }
    }
    
    // finding the minimum strength seam
    int minSeamVal=dpMatrix[H-1][0];
    int minSeamIndex=0;
    for(int i=1;i<W;i++){
        if(minSeamVal>dpMatrix[H-1][i]){
            minSeamVal=dpMatrix[H-1][i];
            minSeamIndex=i;
        }
    }
    // removing the minimum strength seam
    for(int i=H-1;i>=0;i--){
        
        int minIndex;
        if(minSeamIndex==0){  
            int b = dpMatrix[i-1][minSeamIndex];
            int c = dpMatrix[i-1][minSeamIndex+1];
            minIndex = b<c ? minSeamIndex : minSeamIndex+1;
        }else if(minSeamIndex==W-1){
            int a = dpMatrix[i-1][minSeamIndex-1];
            int b = dpMatrix[i-1][minSeamIndex]; 
            minIndex = a<b ? minSeamIndex-1 : minSeamIndex;
        }
        else{     
            int a = dpMatrix[i-1][minSeamIndex-1];
            int b = dpMatrix[i-1][minSeamIndex];
            int c = dpMatrix[i-1][minSeamIndex+1];
    
            minIndex =  a<b 
                        ? (a<c?minSeamIndex-1:minSeamIndex+1) 
                        : (b<c?minSeamIndex:minSeamIndex+1) ;
        }
    
        for(int j=minSeamIndex;j<W-1;j++){
            for(int k=0;k<C;k++){
                rgb[i][j][k]=rgb[i][j+1][k];
            }
            dpMatrix[i][j]=dpMatrix[i][j+1];
        }    
        minSeamIndex=minIndex;
    }
    

}

void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_) {
    // We've provided you the driver.py and main.cpp for your convinience
    // Please go through them and understand the file handling and input/output format
    // Feel free to experiment on your own

    // can access the array using rgb[i][j][k] like a regular 3D array

    // Write your code here
    int verticalSeam = W-W_;
    int horizontalSeam=H-H_;
    
    for(int x=0;x<horizontalSeam;x++){
        removeHorizontalSeam(rgb,H-x,W,C);
    }
    H=H-horizontalSeam;
    for(int x=0;x<verticalSeam;x++){
        removeVerticalSeam(rgb,H,W-x,C);
    }     
    
}

int main() {
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file);

    int H, W, C;
    fin >> H >> W >> C;

    int ***rgb;
    rgb = new int **[H];
    for(int i = 0; i < H; ++i) {
        rgb[i] = new int *[W];
        for(int j = 0; j < W; ++j) {
            rgb[i][j] = new int[C];
            for(int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();

    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;
    solve(rgb, H, W, C, H_, W_, C_);

    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);
    
    fout << H_ << " " << W_ << " " << C_ << endl;
    for(int i = 0; i < H_; ++i) {
        for(int j = 0; j < W_; ++j) {
            for(int k = 0; k < C_; ++k) {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();

    return 0;
}