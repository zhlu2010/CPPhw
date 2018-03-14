#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

class GameofLife{
private:int **table;
    int sot;
    int numofgene;
    int outputgene;
public:
    GameofLife(int i):sot(i){
        table = new int* [sot+2];
        for(int j = 0;j<sot+2;j++)
            table[j] = new int[sot+2];
        for(int k=0;k<sot+2;k++) {
            for (int l = 0; l < sot+2; l++) {
                table[k][l] = 0;
            }
        }
    }
    void readfile(string filename){
        ifstream f(filename);
        string lineBuf;
        getline(f,lineBuf);
        istringstream line(lineBuf);
        line>>numofgene>>outputgene;
        int temp = 1;
        while (!f.eof()) {
            getline(f, lineBuf);
           char ca[sot];
            strcpy(ca, lineBuf.c_str());
            for(int i = 0;i<sot;i++) {
                if (ca[i] == '*') {
                table[i+1][temp] = 1;
            }else {
                    table[i+1][temp] = 0;
                }
            }
            temp++;
        }
    }
    void print(){
        for(int i=1;i<sot+1;i++) {
            for (int j = 1; j < sot+1; j++) {
                if (table[j][i] == 0) {
                cout << '.';
            }else{
                cout << '*';
            }
            }
            cout<<"\n";
        }
    }
    void printnum(){
        for(int i=1;i<sot+1;i++) {
            for (int j = 1; j < sot+1; j++) {
                cout << table[j][i];
            }cout<<"\n";
        }
    }
    void nextGeneration(){
        int temptb[sot][sot];
        for(int i = 0;i<sot;i++){
            for(int j = 0;j<sot;j++){
                int sum = 0;
                sum = table[i][j]+table[i][j+1]+table[i+1][j]+table[i][j+2]+table[i+2][j]+table[i+1][j+2]+table[i+2][j+1]+table[i+2][j+2];
                if(sum<2){
                    temptb[i][j]=0;
                }else if(sum>3){
                    temptb[i][j] = 0;
                }else if (sum == 3){
                    temptb[i][j] = 1;
                }else{
                    temptb[i][j] = table[i+1][j+1];
                }
            }
        }
        for(int i = 0;i<sot;i++) {
            for (int j = 0; j < sot; j++) {
                table[i+1][j+1] = temptb[i][j];
            }
        }
    };
    void result(){
      for(int i = 0;i<=numofgene;i++) {
          if (i % outputgene == 0) {
          print();
        }
        cout<<"\n";
        nextGeneration();
      }
    }

};
int main() {
    GameofLife gl(10);    //the number of girds
    gl.readfile("GameofLife.dat");
    //gl.printnum();
    gl.result();
    return 0;
}