#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <Iterator>
#include <utility>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::map;
using std::vector;
using std::pair;

const char grammer_path[] = "data/grammer.txt"; // the path to the grammer.txt file
const int N = 100; // the max number of Non terminal characters
set<string> Vn,Vt; // the set of non terminal characters and terminal characters
map<string,int> Map; // the map of grammer 
map<int,string> Map2; // the inverse of the map of grammer
vector<vector<string>> v[N]; // the vectors of grammers that begin with each non terminal character
int v_cnt; // the number of non terminal characters

map<string , set<string>> first={ 
    {"$", set<string> {"$"}}
}; // the map of first set for each characters

map<string, set<string> > follow = {
    {"program",set<string> {"#"}}
}; // the map of follow set for each characters

pair<int,int> table[N][N]; // predictive analysis table
map<string,int> vn ; // the map of the characters in the set of Vn
map<string,int> vt ; // the map of the characters in the set of Vt
int cnt_vn ; // the number of characters in the set of Vn
int cnt_vt ; // the number of characters in the set of Vt
const pair<int,int> _00 = {0,-1}; // initialize the table by 

const char lexFile_path[]= "lexical.txt";  // reading file path
const char syntax_analysis_path[]= "syntax_analysis.txt"; // writing file path
int cnt_analysis ; // the No. of analysis
string stack[N]; // the character stack
int top; // the top of the stack
vector<string> chars; // the characters that should be pushed

const char first_file[] = "first.txt";
const char follow_file[] = "follow.txt";
const char table_file[] = "table.txt";

void getVnVt(){
    /*
     * read the grammer.txt and get Vn  wihich the set of non terminal characters  and 
     * Vt which the set of terminal characters
    */
    FILE *fp = freopen(grammer_path, "r", stdin);
    char c;
    vector<string> *right;
    string cur = "";
    bool left=1;
    int Id;
    string str = "";
    int line = 0;
    while((c=getchar())!=EOF){
        if(c=='\n'){
            Vt.insert(cur);
            right ->push_back(cur);
            v[Id].push_back(*right);
            left = 1;
            cur = "";
            continue;
        }
        if(c!=' '&&c!='\t'){
            cur+=c;
            continue;
        } else {
            if(cur=="")continue;
            if(cur=="->"){
                left = 0;
                cur = "";
            } else if(left){
                Id=Map[cur];
                if(Id == 0){
                    Id = ++v_cnt;
                    Map[cur]= Id;
                    Map2[Id]=cur;
                }
                Vn.insert(cur);
                right = new vector<string>;
                cur = "";
            } else {
                right->push_back(cur);
                Vt.insert(cur);
                cur = "";
            }
        }
    }

    for(string token:Vn)Vt.erase(token);
    fclose(fp);

}

void getFirst(string token){
    /*
     * Get the first set of each characters recuresively
    */
    if(first.count(token)>0)return ;
    if(Vt.count(token)){
        set<string> st ;
        st.insert(token);
        first[token] = st;
        return ;
    }
    int Id=Map[token];
    set<string> st;
    for(int i=0;i<v[Id].size();i++){
        vector<string> vv = v[Id][i];
        bool AllHasE = 1;
        for(string str:vv){
            getFirst(str);
            set<string> curset=first[str];
            bool hasE = 0;
            for(string ss:curset){
                if(ss=="$"){
                    hasE=1;
                } else {
                    st.insert(ss);
                }
            }
            if(!hasE){
                AllHasE = 0;
                break;
            }
        }
        if(AllHasE)st.insert("$");        
    }
    first[token]=st;
    for(int i=0;i<v[Id].size();i++){
        vector<string> vv = v[Id][i];
        for(string str:vv){
            getFirst(str);
        }
    }
}


bool getFollow(){
    /*
     * Get the follow sets of non terminal characters 
     * return whether the follow set updated
     * when the follow set did not change after one scanning , stop to call this function 
    */
    bool updated = false;
    for(string token:Vn){
        if(follow.count(token)==0){
            set<string> st ;
            follow[token] = st;
        } 
        set<string> st = follow[token];
        int size_before = st.size();
        for(int i=1;i<=v_cnt;i++){
            for(int j=0;j<v[i].size();j++){
                vector<string> vv = v[i][j];
                bool found = false;
                bool hasNotE = false;
                for(string str:vv){
                    if(found){
                        set<string> curset= first[str];
                        bool hasE = false;
                        for(string cur:curset){
                            if(cur == "$")hasE = true;
                            else st.insert(cur);
                        }    
                        if(!hasE){
                            hasNotE = true;
                            break;
                        }
                    }
                    if(str==token)found = true;
                }
                if(!hasNotE&&found){
                    string head = Map2[i];
                    if(!follow.count(head))continue;
                    set<string> curset = follow[head];
                    for(string cur:curset){
                        st.insert(cur);
                    } 
                }
            }
        }
        if(st.size()!=size_before){
            follow[token] = st;
            updated = true;
        }
    }
    return updated;
}

bool getTable(){
    /*
     * Get the predictive analysis table use ALgorithm which teached in the classs
    */
    cnt_vn = 0;
    for(string token:Vn){
        vn[token]=++cnt_vn; 
    }
    cnt_vt = 0;
    Vt.insert("#");
    for(string token:Vt){
        vt[token]=++cnt_vt;
    }
    for(int i=0;i<=cnt_vn;i++){
        for(int j=0;j<=cnt_vt;j++){
            table[i][j]=_00;
        }
    }
    bool wrong = false;
    for(string token:Vn){
        int Id = Map[token];
        bool hasE = false;
        for(int i=0;i<v[Id].size();i++){
            set<string> st ;
            vector<string> vv = v[Id][i];
            bool theE=true;
            for(string cur:vv){
                bool hasNotE = true;
                set<string> curset = first[cur];
                for(string item:curset){
                    if(item == "$"){
                        hasNotE=false;
                        continue;
                    }
                    st.insert(item);
                }
                if(hasNotE){
                    theE=false;
                    break;
                }
            }
            for(string item:st){
                int id = vt[item];
                if(table[Id][id]!=_00){
                    wrong = true;
                    return wrong;
                }
                table[Id][id]={Id,i};
            }
            if(theE)hasE=true;
        }
        if(hasE){
            set<string> st = follow[token];
            for(string item:st){
                int id = vt[item];
                if(table[Id][id]!=_00){
                    wrong = true;
                    return wrong;
                }
                table[Id][id]={Id,N-1};
            }
        }
    }
    return wrong;
}


void getChars(string str){
    /*
     * Get the chars that shoud be pushed into the stack
    */
    string c1="",c2="",c3="";
    int id = 0;
    while(str[id]!=' '&&str[id]!='\t')c1+=str[id++];
    while(str[id]==' '||str[id]=='\t')id++;
    id++;
    while(str[id]!=',')c2+=str[id++];
    id++;
    while(str[id]!='>')c3+=str[id++];
    if(c2!="Ident"&&c2!="INT"){
        chars.push_back(c1);
    } else chars.push_back(c2);
}

bool doAnalysis(){
    /*
     * do sysntax analysis use predictive analysis table
    */
    FILE *fp = freopen(syntax_analysis_path,"w",stdout);
    auto it = chars.begin();
    while(1){
        string token = stack[top-1];
        if(Vt.count(token)){
            if(token==*it){
                if(token=="#"){
                    // cout << ++cnt_analysis << " " << token << "#" << *it << "\t" << "accept" << endl;
                    cout << ++cnt_analysis << " "  << "EOF#EOF" << "\t" << "accept" << endl;
                    fflush(fp);
                    fclose(fp);
                    freopen("CON","w",stdout);
                    return true;
                }else {
                    cout<< ++cnt_analysis << " " << token << "#" << *it << "\t" << "move" << endl;
                    top--,it++;
                }
            } else {
                cout<< ++cnt_analysis << " " << token << "#" << *it << "\t" << "error" << endl;
                fflush(fp);
                fclose(fp);
                freopen("CON","w",stdout);
                return false;
            }
        } else {
            int Id = Map[token];
            int id = vt[*it];
            if(table[Id][id].second==-1){
                cout<< ++cnt_analysis << " " << token << "#" << *it << "\t" << "error" << endl;
                fflush(fp);
                fclose(fp);
                freopen("CON","w",stdout);
                cout << Id << " " << id << endl;
                cout << "error info : " << token << " " << *it << endl;
                return false;
            } else {
                cout << ++cnt_analysis << " " <<token << "#" << *it << "\t" << "reduction" << endl;
                top--;
                int gId = table[Id][id].second;
                if(gId==99)continue;
                vector<string> vv = v[Id][gId];
                for(int i=vv.size()-1;i>=0;i--){
                    stack[top++]=vv[i];
                }
            }
        }
    }
}

bool analysis(){
    /*
     * read data from file and getChars and doAnalysis
     * return whether the analysis was successful
    */
    stack[top++]="#";
    stack[top++]="program";
    FILE *fp = freopen(lexFile_path,"r",stdin);
    char c ;
    string str="";
    while((c=getchar())!=EOF){
        if(c=='\n'){
            getChars(str);
            str="";
            continue;
        } 
        str+=c;
    }
    fclose(fp);
    chars.push_back("#");
    return doAnalysis();
}

void print_first(){
    FILE *fp = freopen(first_file, "w",stdout);
    for(string token:Vn){
        set<string> st = first[token];
        cout << token << endl << " -- ";
        for(string cur:st){
            cout << "'" <<cur << "' ";
        }
        cout << endl;
    }  
    fflush(fp);
    fclose(fp);
    freopen("CON","w",stdout);
}

void print_follow(){
    FILE *fp = freopen(follow_file, "w",stdout);
    for(string token:Vn){
        set<string> st = follow[token];
        cout << token << endl << " -- ";
        for(string cur:st){
            cout << "'" << cur <<"'" <<  " ";
        }
        cout << endl;
    }
    fflush(fp);
    fclose(fp);
    freopen("CON","w",stdout);
}
void print_table(){
    FILE *fp = freopen(table_file, "w",stdout);
    cout << "   ";
    for(string cur:Vt){
        cout << cur << " ";
    }
    cout << endl;
    for(string token:Vn){
        int Id = Map[token];
        cout << token << " ";
        for(string cur:Vt){
            int id = vt[cur];
            cout << table[Id][id].second << " ";   
        }        
        cout << endl;
    }
    fflush(fp);
    fclose(fp);
    freopen("CON","w",stdout);
}

void syntax(){
    getVnVt();
    // puts("================ grammer has been read =================");
    getFirst("program");
    // puts("================ first set has been created =================");
    print_first();
    while(getFollow());
    // puts("================ follow set has been created =================");
    print_follow();
    if(getTable()){
        puts("the grammer is not LL(1)");
        exit(0);
    }
    // puts("================= Table has been created =================");
    print_table();
    if(!analysis()){
        puts("the lexical info has error(s)");
    }
    // puts("================= sysntax analysis has been finished =================");
}

int main(){
    syntax();
}