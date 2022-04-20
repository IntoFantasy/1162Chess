#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Pair{
    int line1;
    int line2;
};
struct transfer_pair{
    int state1;
    int state2;
};
int m,n,k,cnt;
int broken_judge[201]={0};
long long dp[201][4096]={0};
vector<Pair> state;
vector<transfer_pair> transfer_state;
const long long MOD = 1e9 + 7;

//求出可能的合法状态
bool judge1(int a, int b){
    if(b>>2 & a) return false;
    if(b<<2 & a) return false;
    return true;
}
void State(){
    for(int i=0;i<cnt;++i){
        for(int j=0;j<cnt;++j){
              if(judge1(i, j)) state.push_back({i, j});
        }
    }
}
//可能的状态转移
bool judge2(int S1, int S2){
    int S1_line1=state[S1].line1;
    int S1_line2=state[S1].line2;
    int S2_line1=state[S2].line1;
    int S2_line2=state[S2].line2;
    if(S1_line1>>1&S2_line1) return false;
    if(S1_line1<<1&S2_line1) return false;
    if(S1_line2>>2&S2_line1) return false;
    if(S1_line2<<2&S2_line1) return false;
    if(S1_line2>>1&S2_line2) return false;
    if(S1_line2<<1&S2_line2) return false;
    return true;
}
void transfer_State(){
    for(int i=0;i<state.size();i++){
        for(int j=0;j<state.size();j++){
            if(judge2(i, j)) transfer_state.push_back({i,j});
        }
    }
}

int main() {
    cin>>m>>n>>k;
     cnt = pow(2,n);
    for(int _=0;_<k;++_){
        int a,b;
        cin>>a>>b;
        broken_judge[a]+=pow(2, n-b);
    }
    if(m==1) {
        cout<<n-k;
        return 0;
    }
    State();
    // 初始化前两行
    long long answer=0;
    for(int i=0;i<state.size();i++){
        Pair temp=state[i];
        if(!((broken_judge[1]&temp.line1) || (broken_judge[2]&temp.line2))){
            dp[1][i]=1;
            answer+=1;
        }
    }
    if(m==2){
        cout<<answer;
        return 0;
    }
    answer=0;
    if(m%2==1){
        m+=1;
        broken_judge[m]=63;
    }
    transfer_State();
//    cout<<transfer_state.size()<<endl;
    for(int i=2;i<=m/2;i++){
        for(auto temp:transfer_state){
            if(((broken_judge[2*i-1]&state[temp.state2].line1)||(broken_judge[2*i]&state[temp.state2].line2))) continue;
            else{
                dp[i][temp.state2]=(dp[i-1][temp.state1]+dp[i][temp.state2])%MOD;
//                cout<<state[temp.state2].line2<<endl;
            }
        }
    }
    for(int i=0;i<state.size();i++){
        answer=(answer+dp[m/2][i])%MOD;
    }
    cout<<answer;

    return 0;
}
