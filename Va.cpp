#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class mymap{
	public:
		mymap(int xx,int yy,bool vv);
		bool checkvisit();
		int chx();
		int chy();
		void setv(bool);
			
	private:
		int x;
		int y;
		bool v;
};

mymap::mymap(int xx,int yy,bool vv){
	x = xx;
	y = yy;
	v = vv;
}

void mymap::setv(bool newv){
	v = newv;
}

bool mymap::checkvisit(){
	return v;
}

int mymap::chx(){
	return x;
}

int mymap::chy(){
	return y;
}

vector<mymap*> Wmap;
vector<mymap*> Pace;
vector<char> Pdir; 
vector<mymap*> Pdes;
queue<char>ActQueue;
bool goHome = false;
bool HomeOpen = false;

bool returnHome(){
	bool goHo = true;
        for(int m=0;m< Wmap.size();m++){
                if(Wmap[m]->checkvisit() == false ){
			goHo = false;		
		}
        }
	return goHo;
}

void update(int ux, int uy,char di,char l,char f,char r){
	//left update
	int chl = 0;
	//facing problem
	int lx,ly;
	if(di=='N'){
		lx = ux -1;
		ly = uy;}
	else if(di=='E'){
		lx = ux;
		ly = uy-1;
	}
	else if(di=='S'){
		lx = ux+1;
		ly = uy;
	}
	else if(di=='W'){
		lx = ux;
		ly = uy+1;
	}
	if(l != '1'){
        for(int m=0;m< Wmap.size();m++){
        	if(Wmap[m]->chx() == lx && Wmap[m]->chy() == ly){
                	chl++;
        	}
	}
     	if(chl==0){
		//cout <<"#l---"<<endl;
		mymap* newmap = new mymap(lx,ly,false);
		Wmap.push_back(newmap);
        }
	}
	//front update
	int chf = 0;
	int fx,fy;
	if(di=='N'){
		fx = ux;
		fy = uy-1;}
	else if(di=='E'){
		fx = ux+1;
		fy = uy;
	}
	else if(di=='S'){
		fx = ux;
		fy = uy+1;
	}
	else if(di=='W'){
		fx = ux-1;
		fy = uy;
	}
	if(f != '1'){
        for(int m=0;m< Wmap.size();m++){
                if(Wmap[m]->chx() == fx && Wmap[m]->chy() == fy){
                        chf++;
                }
	}
       	if(chf==0){	
		//cout <<"#f---"<<endl;
                mymap* newmap = new mymap(fx,fy,false);
		Wmap.push_back(newmap);
        }
	}

	//right update
	int chr = 0;
	int rx,ry;
	if(di=='N'){
		rx = ux +1;
		ry = uy;}
	else if(di=='E'){
		rx = ux;
		ry = uy+1;
	}
	else if(di=='S'){
		rx = ux-1;
		ry = uy;
	}
	else if(di=='W'){
		rx = ux;
		ry = uy-1;
	}
	if(r != '1'){
        for(int m=0;m< Wmap.size();m++){
                if(Wmap[m]->chx() == rx && Wmap[m]->chy() == ry){
                        chr++;
                }
        }
       	if(chr==0){
		//cout <<"#r---"<<endl;
        	mymap* newmap = new mymap(rx,ry,false);
		Wmap.push_back(newmap);
        }
	}
	
}


string test(int x,int y,char d,string q){
	
	int px = x;
	int py = y;
	int ox = x;
	int oy = y;
	char pd = d;

	for(int g=0;g<q.length();g++){ //n^2 complex
		bool avoidW = false;
		if(pd == 'N'){
			if( q[g]=='l'){ pd = 'W'; }
			if( q[g]=='f'){ py--; }
			if( q[g]=='r'){ pd = 'E'; }
		}
		else if(pd == 'S'){
                	if( q[g]=='l'){ pd = 'E'; }
                	if( q[g]=='f'){ py++; }
                	if( q[g]=='r'){ pd = 'W'; }
    		}
		else if(pd == 'W'){
                	if( q[g]=='l'){ pd = 'S'; }
                	if( q[g]=='f'){ px--; }
                	if( q[g]=='r'){ pd = 'N'; }
    		}
		else if(pd == 'E'){
                	if( q[g]=='l'){ pd = 'N'; }
                	if( q[g]=='f'){ px++; }
                	if( q[g]=='r'){ pd = 'S'; }
        	}

		for(int m=0;m< Wmap.size();m++){
			if(Wmap[m]->chx() == px && Wmap[m]->chy() == py){
                		avoidW = true;
                	}
		}
	 	if(!avoidW){
			return "failW";
		}

	        //-----------------------------------check end dup

		//-----------does each road cross itself
		for(int z=0; z< Pace.size();z++){
            		if(Pace[z]->chx() == px && Pace[z]->chy() == py && Pdir[z] == pd && g>z){
                		//cout <<"# "<<q<<Pace[z]->chx() <<" "<<Pace[z]->chy() <<" "<<Pdir[z]<< " "<<endl;
				//cout <<"#drop over lap path"<<endl;
				return "failP";
            		}
		}
		mymap* newPace = new mymap(px,py,false);//could use simplify, kill same point
	        Pace.push_back(newPace);
		Pdir.push_back(pd);
		//back to passed road,in one move, drop
	}	
	Pace.clear();
        Pdir.clear();
	
	for(int u = 0;u< Pdes.size();u++){
		if(Pdes[u]->chx() == px && Pdes[u]->chy() == py && q[q.length()-1] == 'f' ){ 
			return "failP";
                }
	}	
	mymap* newPdes = new mymap(px,py,false);//could use simplify, kill same point
        Pdes.push_back(newPdes);

	//check if px and py is unvisited
	for(int m=0;m< Wmap.size();m++){
            if(Wmap[m]->chx() == px && Wmap[m]->chy() == py){
                if(Wmap[m]->checkvisit() == false){//what about open
			Pdes.clear();
			return q;
		}
            }
    	}
	return "fail";
}

void setVisited(int bx,int by){
	for(int sv=0;sv< Wmap.size();sv++){
                if(Wmap[sv]->chx() == bx && Wmap[sv]->chy() == by && Wmap[sv]->checkvisit()==false ){
                        Wmap[sv]->setv(true);
			//cout <<"# visited"<<endl;
                }
        }

}
int countSt = 0;
int main(){
	int x = 150;
	int y = 150;
	char d = 'N'; //update when moving(in action)
	mymap* home = new mymap(x,y,true);
	//cout <<"#only once---------"<<endl;
	Wmap.push_back(home);
	while(1){
		string raw;
		getline(cin,raw);
		//  left <<raw[0]
		//  forward <<raw[2]
		//  right <<raw[4]
		//  vacuum <<raw[6]
		//  off <<raw[8]	         
		update(x,y,d,raw[0],raw[2],raw[4]);//this will not work without action move
		//cout << " #"<<raw[8]<<endl;
		//if(goHome==false){
			if(raw[6] == '1'){
				cout << "vacuum" <<endl;
			}
			else if(raw[8] == '1' && HomeOpen == true){
                                //cout << "# off"<<endl;
                                cout << "off" <<endl;
                        }
			else{
				if(ActQueue.size()<1){
				    queue<string>bfs;
				    bfs.push("f");
			            bfs.push("l");
			            bfs.push("r");
					//keep going forward mess it up
					while(1){
						string result = test(x,y,d,bfs.front());//check for LR string 
						//if (result.find("rl") != string::npos || result.find("lr") != string::npos) {
						//	cout << "# found, and droped------"<<endl;
						//}
						string po = bfs.front();
						if(result.compare("failW") ==0){
								bfs.pop();
						}
						else if(result.compare("failP")==0){
							//cout<<"#failP "<<endl;
							bfs.pop();//droped all, must think of a way to left one thing--------------
						}
						else if(result.compare("fail") == 0){
							bfs.pop();// if there are wall drop instead of push back

							string pof = po +"f";
							//cout <<"#"<<pof<<endl;
							//if(pof.find("frrf")== string::npos && pof.find("fllf")== string::npos
							// )
							bfs.push(pof);//}

                                                        string pol = po +"l";
                                                        if(pol.find("rl") == string::npos && pol.find("lll") == string::npos
							){
							//cout <<"#"<< pol <<endl;
							bfs.push(pol);}

                                                        string por = po +"r";
                                                        if(por.find("lr") == string::npos && por.find("rrr") == string::npos
							){
							//cout <<"#"<< por <<endl;
							bfs.push(por);}
							
						}
						else{
							//cout <<"#The answer "<< result<<endl;
							for(int k = 0;k<result.length();k++){
								ActQueue.push(result[k]);
							}
							break;
						}
						//-------		
						}
					}
				if (ActQueue.size()>0){
				//cout<< "route is here2"<<endl;
				char move = ActQueue.front();
				ActQueue.pop();
				if(d == 'N'){
	                		if( move=='l'){ d = 'W'; 
						cout<<"left"<<endl;
					} 
	 				if( move=='f'){ y-=1; 
						setVisited(x,y);
						//cout <<"# F"<<endl;
						cout<<"forward"<<endl;
					}
		                	if( move=='r'){ d = 'E'; 
						cout<<"right"<<endl;
					}
		        	}
			        else if(d == 'S'){
	        	    		if( move=='l'){ d = 'E'; 
						cout<<"left"<<endl;
					}
	        	        	if( move=='f'){ y+=1; 
						setVisited(x,y);
						//cout <<"# F"<<endl;
						cout<<"forward"<<endl;
					}
	                		if( move=='r'){ d = 'W'; 
						cout<<"right"<<endl;
					}
		        	}
	 			else if(d == 'W'){
	        	        	if( move=='l'){ d = 'S'; 
						cout<<"left"<<endl;
					}
	        		        if( move=='f'){ x-=1; 
						setVisited(x,y);
						//cout <<"# F"<<endl;
						cout<<"forward"<<endl;
					}
	       			        if( move=='r'){ d = 'N'; 
						cout<<"right"<<endl;
					}
	       			 }
	     			else if(d == 'E'){
	                		if( move=='l'){ d = 'N'; 
					cout<<"left"<<endl;
					}
	               		 	if( move=='f'){ x+=1;
						setVisited(x,y);
						//cout <<"# F"<<endl;
						cout<<"forward"<<endl;						
					}
	    		  		if( move=='r'){ d = 'S'; 
						cout<<"right"<<endl;
					}
			 	}
				}

				HomeOpen = returnHome();
                       		if(HomeOpen == true){
					for(int m=0;m< Wmap.size();m++){
                                		if(Wmap[m]->chx() == home->chx() && Wmap[m]->chy() == home->chy()){
                                        		Wmap[m]->setv(false);//set home unvisited
                                        		cout << " # vacuum going home"<<endl;
                                		}
                        		}	
				}
			}
	}			
}

