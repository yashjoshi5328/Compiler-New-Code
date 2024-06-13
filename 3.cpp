// Write a C or C++ program to convert NFA to
// its equivalent DFA
// NFA to DFA

#include<bits/stdc++.h>
using namespace std;
// find x in vector v
bool find(int x,vector<int> v){
	for(int i:v){
		if(x==i)return true;
	}return false;
}
// Find x in a
bool check(int a,int x){
	while(a!=0){
		if(a%10==x)return true;
		a=a/10;
	}
	return false;
}
int main(){
	int total_states=3;
	int nfa[total_states+1][2]={{0}};
	nfa[1][0]=12;
	nfa[1][1]=3;
	nfa[2][0]=1;
	nfa[2][1]=2;
	nfa[3][0]=0;
	nfa[3][1]=12;
	int dfa[20][3]={{0}};
	vector<int> visited;
	visited.push_back(1);
	int max_state=0;
	for(int i=0;i<visited.size();i++){
		if(visited[i]==0) dfa[i][0]=dfa[i][1]=dfa[i][2]=0;
		else if(visited[i]<10){
			if(!find(nfa[visited[i]][0],visited))visited.push_back(nfa[visited[i]][0]);
			if(!find(nfa[visited[i]][1],visited))visited.push_back(nfa[visited[i]][1]);
			dfa[i][0]=visited[i];
			dfa[i][1]=nfa[visited[i]][0];
			dfa[i][2]=nfa[visited[i]][1];
		}
		else{
			int n=visited[i] , a=0 , b=0; 
			while(n!=0){
				int temp=n%10;
				if(nfa[temp][0]==0);
				else if(nfa[temp][0]>a){
					if(!check(nfa[temp][0],a) && a!=0) a=(nfa[temp][0])*10+a;
					else   a=nfa[temp][0];
				}
				else{
					if(!check(a,nfa[temp][0]))a=a*10+(nfa[temp][0]);
				}
				if(nfa[temp][1]==0);
				else if(nfa[temp][1]>b){
					if(!check(nfa[temp][1],b) && b!=0)b=(nfa[temp][1])*10+b;
					else	b=nfa[temp][1];
				}
				else{
					if(!check(b,nfa[temp][1]))b=b*10+(nfa[temp][1]);
				}
				n=n/10;
			}
			dfa[i][0]=visited[i];
			dfa[i][1]=a;
			dfa[i][2]=b;
			if(!find(a,visited))visited.push_back(a);
			if(!find(b,visited))visited.push_back(b);
		}
		max_state++;
	}
	cout<<"state\t"<<"a\t"<<"b\t"<<endl;
	for(int i=0;i<max_state;i++){
		for(int j=0;j<3;j++){
			cout<<dfa[i][j]<<"\t";
		}
		cout<<endl;
	}
}