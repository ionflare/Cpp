#include <iostream>

using namespace std;
//int a[999][2][3] = {{{1,1,1},{2,2,2}}}; 



class Servo{
    private :
        int pinIdx;
        int pwdMax;
        
        int pwdMin;
        int counter = 1;// defualt
        bool move = false;
        int pwdTarget;
        
        bool isClockwise = true;
        int dirMultiplier = 1;

        //4 quadrants, [0Pi -> 1/2Pi -> 1Pi -> 3/2Pi ]  
        int pwdAtQuadrant[4];
        // 1degree = ?pwd, 4 quadrants, [1/2 Pi -> 1Pi -> 3/2Pi -> 2Pi ]  
        float pwdPerDeg[4];
    public :
        Servo(int pinId, int dMin,int dMax, int pStQd[4], int ppd[4]){
            pinIdx = pinId;

            if(pStQd[0] < pStQd[1]){
                isClockwise = true;
            }
            else{ 
                isClockwise = false; 
            }
            pwdPerDeg[0] = (pwdAtQuadrant[1] - pwdAtQuadrant[0]) / 90;
            pwdPerDeg[1] = (pwdAtQuadrant[2] - pwdAtQuadrant[1]) / 90;
            pwdPerDeg[2] = pwdPerDeg[1];
            pwdPerDeg[3] = pwdPerDeg[0];
            pwdMax = cnvDegToPwd(dMax);
            pwdMin = cnvDegToPwd(dMin);
        }
        double getCurrentDeg(int pwd){
            return 0;
        }
        void tick(){
            if(move){
                if(getServoCurrentPwd() == pwdTarget){
                    move = false;
                }
            }else{
                counter = getServoCurrentPwd() + dirMultiplier;
                Rotate();
            }
        }
        void setRotatePwd(int deg){
            switch ((deg/90) % 4)
            {
            case 0:
                pwdTarget = pwdAtQuadrant[0] + (deg * pwdPerDeg[0]);    
                break;
            case 1:
                pwdTarget =  pwdAtQuadrant[1] + ((deg % 90) * pwdPerDeg[1]);   
                break;
            case 2:
                pwdTarget = pwdAtQuadrant[2] + ((deg % 90) * pwdPerDeg[2]);   
                break;
            case 3:
                pwdTarget = pwdAtQuadrant[3] + ((deg % 90) * pwdPerDeg[3]);
                break;
            default:
                pwdTarget = pwdAtQuadrant[0] + (deg * pwdPerDeg[0]);    
                break;
            }
            if(pwdTarget > pwdMax) {pwdTarget = pwdMax;} 
            if(pwdTarget < pwdMin) {pwdTarget = pwdMin;}



            counter = getServoCurrentPwd();
            if(getServoCurrentPwd() >= pwdTarget){
                dirMultiplier = 1;
            }else{
                dirMultiplier = -1;
            }
            move = true;
        }

        int getServoCurrentPwd(){
            return 1;
        }
        void Rotate(){}
        
        int cnvDegToPwd(int deg){
            int res = 0;
            switch ((deg/90) % 4)
            {
            case 0:
                res = pwdAtQuadrant[0] + (deg * pwdPerDeg[0]);    
                break;
            case 1:
                res =  pwdAtQuadrant[1] + ((deg % 90) * pwdPerDeg[1]);   
                break;
            case 2:
                res = pwdAtQuadrant[2] + ((deg % 90) * pwdPerDeg[2]);   
                break;
            case 3:
                res = pwdAtQuadrant[3] + ((deg % 90) * pwdPerDeg[3]);
                break;
            default:
                res = pwdAtQuadrant[0] + (deg * pwdPerDeg[0]);    
                break;
        }
        return res;
    }
};
int main()
{
    std::cout <<  92/5 << std::endl;
    //cout << a[991][1][1];
    // double inp; 
    // while(1){
    //     std::cout << "Hello World" << std::endl;
    //     std::cin >> inp;
    //     std::cout << inp << std::endl;
    // }
    return 0;
}



