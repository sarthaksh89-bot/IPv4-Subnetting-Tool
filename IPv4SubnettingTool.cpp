#include <iostream>
#include <math.h>
#include <stack>
using namespace std;
void ipr(int &q,int &r,int &s,int &t,int ip[],int &n,int chart1[],int &sb){
    int k,f;
    int oct = (n-1)/8;
    int bio = (n-1)%8;
    int inc = pow(2, 7 - bio);
    cout << "\nTotal Subnets Generated: " << sb << "\n"; 
    cout <<"\nBlock Size Increment : " << inc << "\n";
    cout << "                                      SUBNET RANGE TABLE                       \n";
    cout <<"                Subnet | Network Address |Usable Host Range | Broadcast Address\n";
    cout << "           ----------------------------------------------------------------------------\n";

    int base_ip[4] = {ip[0], ip[1], ip[2], ip[3]};

    for (int i = 0; i < sb; i++) {
        int current_octet_val = (i * inc) % 256;
        int current_end = current_octet_val + inc - 1;
        int higher_octet_offset = (i * inc) / 256;

        if (oct == 1) {
            cout << (i + 1) << "\t\t"
                 << base_ip[0] << "." << (base_ip[1] + higher_octet_offset) << "." << current_octet_val << ".0\t\t"
                 << base_ip[0] << "." << (base_ip[1] + higher_octet_offset) << "." << current_octet_val << ".1 - " 
                 << base_ip[0] << "." << (base_ip[1] + higher_octet_offset) << "." << current_end << ".254\t"
                 << base_ip[0] << "." << (base_ip[1] + higher_octet_offset) << "." << current_end << ".255\n";
        }
        else if (oct == 2) {
            cout << (i + 1) << "\t\t"
                 << base_ip[0] << "." << base_ip[1] << "." << (base_ip[2] + higher_octet_offset) << "." << current_octet_val << "\t\t"
                 << base_ip[0] << "." << base_ip[1] << "." << (base_ip[2] + higher_octet_offset) << "." << (current_octet_val + 1) << " - " 
                 << base_ip[0] << "." << base_ip[1] << "." << (base_ip[2] + higher_octet_offset) << "." << (current_end - 1) << "\t"
                 << base_ip[0] << "." << base_ip[1] << "." << (base_ip[2] + higher_octet_offset) << "." << current_end << "\n";
        }
        else if (oct == 3) {
            cout << (i + 1) << "\t\t"
                 << base_ip[0] << "." << base_ip[1] << "." << base_ip[2] << "." << current_octet_val << "\t\t"
                 << base_ip[0] << "." << base_ip[1] << "." << base_ip[2] << "." << (current_octet_val + 1) << " - " 
                 << base_ip[0] << "." << base_ip[1] << "." << base_ip[2] << "." << (current_end - 1) << "\t"
                 << base_ip[0] << "." << base_ip[1] << "." << base_ip[2] << "." << current_end << "\n";
        }
    }
}
void nsm(stack<int> &stak,int chart1[],int &n,int nsubm[]){
    stack<int> temp;
    while(!stak.empty()){
        temp.push(stak.top());
        stak.pop();
    }
    cout<<"\nNew Subnet Mask = ";
    for(int i=0;i<4;i++){
        int k = 0,j=0;
        while(j<8 && !temp.empty()){
            int val = temp.top();
            temp.pop(); 
            if(val == 8){
                continue; 
            }    
            if(val == 1){
                k += chart1[j];    
            }
            j++;    
        }
    nsubm[i] = k;
    cout<<nsubm[i]<<(i<3 ? "." : "");    
    }             
}
bool sbnh(int &h,int &n,stack<int> &stak,int &m,int chart2[],int host,int &hsb,int &sb){
    int rhb = 0;

    while (((1 << rhb) - 2) < hsb) { 
        rhb++; 
    }

    if (rhb > h) {
        cout << "\nError: Requested hosts exceed total available host bits in this class!\n";
        return false;
    }
    int ohb = h;
    int bb = ohb - rhb;

    cout<<"Total Host Bits to be borrow =  "<<bb;
    h -= bb;
    n += bb;
    m = h+n;
    int nb = n,hb = h;

    sb = (1 << bb);
    while (!stak.empty()) stak.pop();
    int val;
    for(int i=1;i<=m;i++){
        if(i<=nb){
            val = 1;
            stak.push(val);
        }
        else{
            val = 0;
            stak.push(val);
        }
        if(i%8 == 0 && i<32){
            val = 8;
            stak.push(val);
        }
    }
    stack<int> temp;
    while(!stak.empty()){
        temp.push(stak.top());
        stak.pop();
    }
    cout<<"\nNew Binary Subnet Mask = ";    
    while(!temp.empty()){
        val = temp.top();
        if(val == 1 || val == 0){
            cout<< val;
        }
        else if(val == 8){
            cout<<".";
        }
        stak.push(val);
        temp.pop();
    }
    return true;
}
bool sbnn(int &h,int &n,stack<int> &stak,int &m,int chart2[],int host,int &hsb,int &sb){
    int count = 0;
    while (pow(2, count) < sb) {
        count++;
    }
    if (count > h) {
        cout << "\nError: Requested subnets exceed available host bits!\n";
        return false;
    }
    cout<<"Total Host Bits to be borrow =  "<<count;
    h -= count;
    n += count;
    m = h+n; 

    while (!stak.empty()) stak.pop();
    int nb = n;
    
    for (int i = 1; i <= m; i++) {
        if (i <= nb){
            stak.push(1);
        }
        else{
            stak.push(0);
        }
        if (i % 8 == 0 && i < 32){
            stak.push(8);
        }    
    }
    stack<int> temp;
    while(!stak.empty()){
        temp.push(stak.top());
        stak.pop();
    }
    int val;
    cout<<"\nNew Binary Subnet Mask = ";    
    while(!temp.empty()){
        val = temp.top();
        if(val == 1 || val == 0){
            cout<< val;
        }
        else if(val == 8){
            cout<<".";
        }
        stak.push(val);
        temp.pop();
    }
    return true;
}
void smb(int subm[],int chart1[],int &h,int &n){
    for(int i=0;i<4;i++){
        int k = subm[i];
        for(int j=0;j<8;j++){
            if(k>=chart1[j]){
                cout<<"1";
                k = k - chart1[j];
                n++;
            }
            else{
                cout<<"0";
                h++;
            }
        }
        cout<<".";
    }
}
int main() {
    while(1){
    int a=0, b=0, c=0, d=0, x=0, y=0, z=0, w=0, q=0, r=0, s=0, t=0;
    char dot1,dot2,dot3;
    int h = 0,n = 0,m = 0;
    stack<int> stak;
    cout<<"Enter your Ipv4 Address :";
    if(!(cin >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d) || 
        (dot1 != '.' || dot2 != '.' || dot3 != '.')){
        cout<<"Invalid Inpt Format";
        cin.clear();
        cin.ignore(10000, '\n'); 
        continue;
    }
    if(a<0 || a>255 || b<0 || b>255 || c<0 || c>255 || d<0 || d>255){
        cout<<"Invalid IPv4 Address";
        continue;
        }
    if(a == 10 && b>=0 && b<=255 && c>=0 && c<=255 && d>=0 && d<=255){
        cout<<"Private Network in Class A";
        x = 255; y = 0; z = 0; w = 0;
    }
    else if(a == 172 && b>=16 && b<=31 && c>=0 && c<=255 && d>=0 && d<=255){
        cout<<"Private Network in Class B";
        x = 255; y = 255; z = 0; w = 0;
    }
    else if(a == 192 && b == 168 && c>=0 && c<=255 && d>=0 && d<=255){
        cout<<"Private Network in Class C";
        x = 255; y = 255; z = 255; w = 0;
    }
    else if(a == 127){
        cout<<"Loop Back Addresses";
        continue;
    }    
    else if(a>=1 && a<=126){
        cout<<"Public Network in Class A";
        x = 255; y = 0; z = 0; w = 0;
    }
    else if(a>=128 && a<=191){
        cout<<"Public Network in Class B";
        x = 255; y = 255; z = 0; w = 0;
    }
    else if(a>=192 && a<=223){
        cout<<"Public Network in Class C";
        x = 255; y = 255; z = 255; w = 0;
    }
    else if(a>=224 && a<=239){
        cout<<"Class D (Multicast)Network";
        continue;
    }
    else if(a>=240 && a<=255){
        cout<<"Class E (Experimental/Research)Network";
        continue;
    } 
    else{
        cout<<"Invalid IPv4 Address";
        continue;
    }
    int ip[4] = {a,b,c,d};
    int subm[4] = {x,y,z,w};
    int nsubm[4];
    int nipr[4] = {q,r,s,t};
    int chart1[8] = {128,64,32,16,8,4,2,1};
    int chart2[8] = {2,4,8,16,32,64,128,256};
    cout<<"\nBinary Subnet Mask = ";
    smb(subm,chart1,h,n);
    int host = (pow(2,h)-2);
    int cho;
    int sb,hsb;
    cout<<"\n";
    cout<<"1-> As per Host: ";
    cout<<"2-> As per Network: ";
    cout<<"\n";
    cin>>cho;
    bool success = false;
    if (cho == 1) {
        cout << "\nEnter hosts per each network: ";
        cin >> hsb;
        success = sbnh(h, n, stak, m, chart2, host, hsb, sb);
    } 
    else {
        cout << "\nEnter the Subnets required: ";
        cin >> sb;
        success = sbnn(h, n, stak, m, chart2, host, hsb, sb);
    }
    if (success) {
        nsm(stak, chart1, n, nsubm);
        ipr(q, r, s, t, ip, n, chart1, sb);
    }
    char choice;
        cout << "\nDo you want to exit? [y/n]: ";
        cin >> choice;
        if (choice == 'y') {
            cout << "Exiting program. Goodbye!\n";
            return 0;
        } 
        else if (choice == 'n') {
            cout << "\n----------------------------------------\n\n";
            
        } 
        else {
            cout << "Invalid choice! Continuing program...\n\n";
            
        }
    }
    return 0;
}

