#include <iostream>
using namespace std;

class Rectangle{

    private:
        int width;
        int length;

    public:

    Rectangle() : width(1), length(1){

    } 

    Rectangle(int w, int l) : width(w), length(l){

    }


    int getWidth(){
        return width;
    }

    int getLength(){
        return length;
    }

    Rectangle operator+(Rectangle other ){
        int newWidth = this->width + other.width;
        int newLength = this->length + other.length;

        Rectangle result (newWidth, newLength);
        return result;
    }


    Rectangle operator* (int num){
        int newWidth = this->width * num;
        int newLength = this->length * num;

        Rectangle result (newLength, newWidth);
        return result;
    }

    void print(){
        cout << "Rectangle width: " << width << " height: " << length << endl;
    }
    

};

  int main(){  /// keep outside thr CPP 'class'
        Rectangle r1 (3, 4);
        Rectangle r2 (10, 2);

        Rectangle r3 = r1 + r2; // r1.add(r2): Java - way
        Rectangle r4 = r1.operator+(r2); // what's happening under the hood of r1+r2 (line above)

        r3.print();

        return 0;
    }