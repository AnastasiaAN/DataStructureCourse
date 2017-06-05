#include <iostream>
using namespace std;

int main(){
		int a=0;
		int b=0;
		int c=0;
		int temp=0;
	  cin>>a>>b>>c;
	  if (a>b){
	      temp=a;
	      a=b;
	      b=temp;
	  }
	  if (b>c){
	      temp=b;
	      b=c;
	      c=temp;
	  }
	  if (a>b){
	      temp=a;
	      a=b;
	      b=temp;
	  }

		cout<<a<<","<<b<<","<<c<<endl;
		return 0;
}
