#include <bits/stdc++.h>
#define sc scanf
#define pf printf
#define pb push_back
#define ff first
#define ss second
#define bs binary_search
#define fread freopen("input.txt","r",stdin)
#define pb push_back
using namespace std;

int n;
int rss,css;
int arrr[1001][1001];
int columns2[1001];
int columns[1001];
int ij[2];
vector<int>ansIndex;
vector<int>ck;
vector<int>finalAns;
//string var[26]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
//string lit[26]={"A'","B'","C'","D'","E'","F'","G'","H'","I'","J'","K'","L'","M'","N'","O'","P'","Q'","R'","S'","T'","U'","V'","W'","X'","Y'","Z'"};
string var[100];
string lit[100];
string toBinary(int num){
	string str="";
	while(num>0){
		if(num%2==0)str="0"+str;
		else str="1"+str;
		num=num/2;
	}
	int sz = str.size();
//	cout<<sz<<" "<<n<<endl;
	while(sz<n){
		str="0"+str;
		sz++;
	}
	return str;
}


vector<string> quine(vector<string> SOP){
	map<int , vector<string> > step;
	map<int, vector<string> >::iterator it;
	int sz = SOP.size();

	for(int i=0;i<sz;i++){
		int one=0;
		string str = SOP[i];
		for(int j=0;j<n;j++){
			if(str[j]=='1')one++;
		}
	//	cout<<str<<" "<<one<<endl;
		step[one].pb(str);
	}

	sz = step.size();

	map<string,int>check;
	vector<string>store;
	bool c = true;
	for(it=step.begin();it!=step.end();){
		/*int temp = it->ff;
		cout<<temp<<endl;
		int w = step[temp].size();

		for(int j =0 ;j<w;j++){
			cout<<step[temp][j]<<" ";
		}
		cout<<endl;
		*/

		int u = it->ff;
		it++;
		if(it==step.end())break;
		int v = it->ff;

		int szu = step[u].size();
		int szv = step[v].size();

	//	cout<<szu<<" "<<szv<<endl;

		for(int i=0;i<szu;i++){
			string str1 = step[u][i];
			for(int j=0;j<szv;j++){
				int dif=0;
				int dpos=0;
				string str = str1;
				string str2 = step[v][j];
				for(int k=0;k<n;k++){
					if(str[k]!=str2[k]){
						dif++;
						dpos=k;
					}
				}
				if(dif==1&&(str[dpos]!='_'&&str2[dpos]!='_')){
					check[str1]=1;
					check[str2]=1;
					str[dpos]='_';
					store.pb(str);
					c=false;

				}
			}
		}




	}
	sz =SOP.size();
	for(int i=0;i<sz;i++){
		string ss = SOP[i];
		if(check[ss]!=1){
			store.pb(ss);
			//c=false;
		}
	}

/*	for(int i=0;i<store.size();i++){
		cout<<store[i]<<endl;
	}
	cout<<endl;*/

            if(c==true)return SOP;
	return quine(store);
}

bool cmp(string a,string b){
    int an=0;
    int bn=0;
    for(int i=0;i<n;i++){
        if(a[i]=='_')an++;
    }

    for(int i=0;i<n;i++){
        if(b[i]=='_')bn++;
    }

    if(an>bn)return true;
    return false;

}
void unionn(vector<int>options){
    for(int i =0;i<css;i++){
        int x = options[ij[0]];
        int y = options[ij[1]];
        if(arrr[x][i]+arrr[y][i]>0){
            arrr[x][i]=0;
            arrr[y][i]=0;
            columns2[i]=1;
        }
    }
}

void distinct(vector<int>options){
    int rowjoined=1;
    int mxx =0;
    ij[0]=0;
    ij[1]=0;

    int sz = options.size();

    if(sz==1){
        for(int i=0;i<css;i++){
            int x = options[0];
            if(arrr[x][i]==1&&columns2[i]==0){
                arrr[x][i]=0;
                columns2[i]=1;
            }
        }
        ansIndex.pb(options[0]);
        return;
    }

    for(int i=0;i<options.size();i++){
        for(int j=i+1;j<options.size();j++){
            int dis =0;

            for(int l=0;l<css;l++){
                int x = options[i];
                int y = options[j];
                if(arrr[x][l]+arrr[y][l]>0)dis++;
            }

            if(dis>mxx){
                mxx = dis;
                ij[0]=i;
                ij[1]=j;
                if(mxx>1)rowjoined=2;

            }
        }
    }

    if(mxx!=0){
        unionn(options);

        int a = options[ij[0]];
        int b = options[ij[1]];
        if(mxx>1){
            ansIndex.pb(a);
            ansIndex.pb(b);
        }
        else ansIndex.pb(a);

    }


}

void mcclusky(vector<string> SOP,vector<string> pImplican){
    css = SOP.size();
	rss = pImplican.size();


	//sort(pImplican.begin(),pImplican.end(),cmp);
	//int arrr[rss][css];

	/*for(int i=0;i<SOP.size();i++){
		cout<<SOP[i]<<" ";
	}*/

	//sort(pImplican.begin(),pImplican.end(),cmp);

	/*for(int i=0;i<pImplican.size();i++){
        cout<<pImplican[i]<<" ";
	}*/

	//cout<<endl;

	for(int i=0;i<rss;i++)
        for(int j=0;j<css;j++)arrr[i][j]=0;

    for(int j=0;j<css;j++)columns[j]=0;


	for(int i=0;i<rss;i++){
		string str1=pImplican[i];
		int counter=0;
		//cout<<str1<<endl;
		for(int j=0;j<css;j++){
			string str =str1;
			string str2=SOP[j];
			int dif=0;
			for(int k=0;k<n;k++){
			if(str[k]!='_'&&(str[k]!=str2[k]))dif++;
			}
			if(dif==0){
                    arrr[i][j]=1;
                    columns[j]=1;
                    counter++;
			}
			}
			if(counter==0)ck.pb(i);

		}

		/*for(int i=0;i<rss;i++){
            for(int j=0;j<css;j++){
                cout<<arrr[i][j]<<" ";
            }
            cout<<endl;
		}*/

		for(int i=0;i<css;i++)columns2[i]=0;

		while(1){
            vector<int>options;
            int mxx=0;
            for(int i=0;i<rss;i++){
                int counter =0;

                for(int j=0;j<css;j++){
                    if(arrr[i][j]==1&&columns[j]==1&&columns2[j]==0)counter++;
                }

                if(counter>mxx){
                    mxx=counter;
                    options.clear();
                    options.pb(i);
                }
                else if(counter==mxx){
                    mxx = counter;
                    options.pb(i);
                }
            }


            if(mxx!=0){
                distinct(options);
                options.clear();
            }
            else break;
		}


		//cout<<ansIndex.size()<<endl;

	/*for(int i=0;i<rss;i++){
        for(int j=0;j<css;j++){
            cout<<arrr[i][j]<<" ";
        }
        cout<<endl;
	}/*


	map<string,int>ans;

	for(int i=0;i<rss;i++){
		ans[pImplican[i]]=0;
	}
/*	cout<<"     ";
	for(int i=0;i<cs;i++){
		cout<<SOP[i]<<" ";
	}
	cout<<endl;

	for(int i=0;i<rs;i++){
		cout<<pImplican[i]<<endl;
	}
	*/


	/*cout<<" "<<endl;

	for(int i=0;i<rss;i++){
        int mx =0;
        int mp =0;
        for(int j=0;j<rss;j++){
            int sum=0;
            string str = pImplican[j];
            if(ans[str]==1)continue;
            for(int k=0;k<css;k++){
                if(arrr[j][k]==1){
                    for(int l=0;l<rss;l++){
                        sum+=arrr[l][k];
                    }
                }
            }
            if(sum>mx){
                mx=sum;
                mp=j;
            }
        }
        cout<<mx<<" "<<mp<<endl;
        if(mx==0)break;

                for(int y=0;y<rss;y++){
            for(int z=0;z<css;z++){
                cout<<arrr[y][z]<<" ";
            }
            cout<<endl;
        }

        cout<<endl;


        ans[pImplican[mp]]=1;
        for(int m=0;m<css;m++){
            if(arrr[mp][m]==1){
                for(int o=0;o<rss;o++){
                    arrr[o][m]=0;
                }
            }
        }

        for(int y=0;y<rss;y++){
            for(int z=0;z<css;z++){
                cout<<arrr[y][z]<<" ";
            }
            cout<<endl;
        }
	}

	map<string,int>::iterator it;
	for(it=ans.begin();it!=ans.end();it++){
        string str = it->ff;
        if(ans[str]==1)cout<<str<<endl;
	}
	*/
}


void print(vector<string>pImplican){
    cout<<"ans :";
    int sz = finalAns.size();
    //cout<<sz<<endl;
    if(sz==0)cout<<"Minimization not possible"<<endl;

    string arr[sz];

    for(int i=0;i<sz;i++){
            int x = finalAns[i];
        string str=pImplican[x];
        string astr="";
        for(int j=0;j<n;j++){
            if(str[j]=='0')astr+=lit[j];
            else if(str[j]=='1')astr+=var[j];
        }
        arr[i]=astr;
    }

    if(sz==1){
        cout<<arr[0]<<endl;
    return;
    }
    cout<<arr[0];
    for(int i=1;i<sz;i++){
        cout<<" + "<<arr[i];
    }
    cout<<endl;
    finalAns.clear();

}

int main() {

    //fread;

    cout<<"     //***Tabulation Method****\\\\\n"<<endl;
    cout<<endl;

	//it takes the number of total variables
	int c =0;
	cout<<"Number of varibales : "<<endl;
	while(sc("%d",&n)==1){
    if(c!=0)cout<<endl;

    //

	string ajaira;
	getline(cin,ajaira);
	for(int i=0;i<n;i++){
        cout<<"variable "<<i+1<<" : ";
	    string a;
        cin>>a;
        var[i]=a;
        lit[i]=a+"'";
        cout<<endl;
	}
	cout<<endl;
	int nSOP;
	//takes input as sum of product (SOP)
	cout<<"Enter number of minterms: "<<endl;
	sc("%d",&nSOP);

	vector<string>SOP;
	vector<int>minterms;
	vector<int>donot;
	vector<string>mSOP;

	//cout<<nSOP<<endl;
	for(int i=0;i<nSOP;i++){
		int x;
		cout<<"Minterm "<<i+1<<" : ";
		sc("%d",&x);
		cout<<endl;
		//cout<<x<<" ";
		minterms.pb(x);
		SOP.pb(toBinary(x));
		mSOP.pb(SOP[i]);
	}
	cout<<endl;

	int d;
	cout<<"Enter number of don't cares :" <<endl;
	sc("%d",&d);
	//cout<<d<<endl;
	for(int i=0;i<d;i++){
		int x;
		//taking input of SOP of don't cares
		cout<<"don't care "<<i+1<<": ";
		sc("%d",&x);
		donot.pb(x);
		cout<<endl;
		SOP.pb(toBinary(x));
	}
	if(d>0)cout<<endl;


	vector<string>pImplican = quine(SOP);
	sort(pImplican.begin(),pImplican.end(),cmp);
	int t = pImplican.size();
	map<string,int>temp;
	map<string,int>::iterator it;
	for(int i=0;i<t;i++)temp[pImplican[i]]=1;
	pImplican.clear();

	for(it=temp.begin();it!=temp.end();it++){
		string x = it->ff;
		pImplican.pb(x);
	}
/*	int sz = pImplican.size();
	for(int i=0;i<sz;i++){
		string str = pImplican[i];
		//cout<<str<<endl;
		string ans = "";
		for(int j=0;j<n;j++){
			if(str[j]=='0')ans+=lit[j];
			else if(str[j]=='1')ans+=var[j];
		}
		cout<<ans<<endl;
	}
	cout<<endl;

*/
    pf("\n\n\n");
    cout<<"***** case :"<<++c<<"*****\n"<<endl;
    cout<<"number of variables : "<<n<<endl;
    cout<<"variables :";
    for(int i=0;i<n;i++){
        cout<<var[i];
        if(i==n-1)cout<<endl;
        else cout<<",";
	}

	 cout<<"number of minterms : "<<nSOP<<endl;

    cout<<"minterms :";
    for(int i=0;i<nSOP;i++){
        cout<<minterms[i];
        if(i==nSOP-1)cout<<endl;
        else cout<<",";
	}

    cout<<"number of don't cares : "<<d<<endl;

    if(d>0)cout<<"don't cares :";
    for(int i=0;i<d;i++){
        cout<<donot[i];
        if(i==d-1)cout<<endl;
        else cout<<",";
	}


	mcclusky(mSOP,pImplican);
	//finalAns.clear();
	sort(ansIndex.begin(),ansIndex.end());
    ansIndex.erase( unique( ansIndex.begin(), ansIndex.end() ), ansIndex.end() );
	//cout<<1<<endl;
	//cout<<ansIndex.size()<<endl;
	finalAns.clear();
	int r = ansIndex.size();
	for(int i=0;i<r;i++){
        if(bs(ck.begin(),ck.end(),ansIndex[i])==0){
        finalAns.pb(ansIndex[i]);
        }
	}
	ansIndex.clear();
	ck.clear();
	print(pImplican);
	}
	return 0;
}
