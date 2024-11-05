#include<iostream>
int main(){
    int price;
    std::cout<<"enter price";
    std::cin>>price;
    if(price<100){
        std::cout<<"no discount "<<price;
    }else if(price>=100 && price<500){
        price=price-(0.10*price);
        std::cout<<"the discounted price is"<<price;
    }
    else if(price>=500 && price<1000){
        price=price-(0.15*price);
        std::cout<<"the discounted price is"<<price;
}
else if(price>=1000){
        price=price-(0.20*price);
        std::cout<<"the discounted price is"<<price;
}else if(price>=10000){
 std::cout<<"error";
}else if(price<0){
  std::cout<<"error";
  return 0;
}
