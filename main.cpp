#include <iostream>
#include <vector>

using namespace std;

// global variable
vector<int> count_vec;
int init_x1;
int init_y1;
int curr_x1;
int curr_y1;


int a = 2;
int b = 3;
int m = 17;

#define ma_mod(a,n) ((a%n)+n)%n;

// y^2 = x^3 + 2x + 3 mod 17



int modInverse(int a, int m)
{
    for (int x = 1; x < m; x++)
        if (((a%m) * (x%m)) % m == 1)
            return x;

    return 0;
}



void convertToBinary(unsigned int n)
{
    if (n / 2 != 0) {
        convertToBinary(n / 2);
    }
    count_vec.emplace_back(n%2);
    //cout<<n%2;
}

int ecc_mult(){
    int s_top = (3*curr_x1*curr_x1 + a);
    int s_buttom = 2*curr_y1;
    //cout<<s_top<<" "<<s_buttom<<endl;
    if(s_top<0) s_top = ma_mod(s_top,m);
    if(s_buttom<0) s_buttom = ma_mod(s_buttom,m);

    int s_inv = modInverse(s_buttom,m);
    return ma_mod((s_top*s_inv), m);
}

int ecc_add(){
    int s_top = (init_y1 -  curr_y1);
    int s_buttom = (init_x1 - curr_x1);

    if(s_top<0) s_top = ma_mod(s_top,m);
    if(s_buttom<0) s_buttom = ma_mod(s_buttom,m);

    int s_inv = modInverse(s_buttom,m);
    return ma_mod((s_top*s_inv), m);
}

void ECC(){
    for(int i=0;i<count_vec.size();i++){
        //cout<<count_vec[i];
        if(i==0) continue;
        int s;
        int x3,y3;
        
        
        s = ecc_mult();
        x3 = ma_mod((s*s - curr_x1 - curr_x1), m);
        y3 = ma_mod((s*(curr_x1 - x3) - curr_y1), m);
        curr_x1 = x3;
        curr_y1 = y3;
        cout<<i<<" "<<s<<" "<<curr_x1<<" "<<curr_y1<<" "<<endl;

        if(count_vec[i]==1){
            s = ecc_add();
            x3 = ma_mod((s*s - curr_x1 - init_x1), m);
            y3 = ma_mod((s*(curr_x1 - x3) - curr_y1), m);
            curr_x1 = x3;
            curr_y1 = y3;
            cout<<i<<" "<<s<<" "<<curr_x1<<" "<<curr_y1<<" "<<endl;
        }
    }

}



int main(){
    
    int count = 26;
    init_x1 = 5;
    init_y1 = 11;

    curr_x1 = 5;
    curr_y1 = 11;

    cout<<"Private Key:";
    cin>>count;
    cout<<"Public Key (x,y)\n";
    cout<<"x:";
    cin>>init_x1;
    cout<<"y:";
    cin>>init_y1;
    curr_x1 = init_x1;
    curr_y1 = init_y1;
    
    cout<<"y^2 = x^3 + ax + b"<<endl;
    cout<<"a:";
    cin>>a;
    cout<<"b:";
    cin>>b;
    
    
    convertToBinary(count);
    ECC();
    return 0;
}