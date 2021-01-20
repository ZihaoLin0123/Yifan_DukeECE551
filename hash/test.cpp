#include <iostream>
#include <map>
#include <list>
#include <fstream>
using namespace std;

class StringHasher{
private:
    const int multiplyBy;
public:
    StringHasher():multiplyBy(29){}
    StringHasher(int m):multiplyBy(m){}
    unsigned operator()(const string & str) const{
        unsigned ans = 0;
        for (string::const_iterator it = str.begin(); it != str.end(); ++it){
            ans = ans * multiplyBy + *it;
        }
        return ans;
    }
};

int main(){
    int factor = 1;
    ifstream f("/usr/share/dict/words");
    StringHasher hash(factor);
    map<unsigned, list<string> > table;
    map<unsigned, unsigned> d;
    map<unsigned, unsigned>::iterator dis;
    string str;
    map<unsigned, list<string> >::iterator it;
    while(getline(f, str)){
        unsigned key = hash(str);
        it = table.find(key);
        if(it != table.end()){
            it->second.push_front(str);
        }else{
            list<string> l;
            l.push_front(str);
            table.insert(pair<unsigned, list<string> >(key, l));
        }
    }

    for (it = table.begin(); it != table.end(); ++it){
        int sz = it->second.size() - 1;
        dis = d.find(sz);
        if(dis != d.end()){
          ++(dis->second);
        }else{
          d.insert(pair<unsigned, unsigned>(sz, 1));
        }
    }
    
    for(dis = d.begin(); dis != d.end(); ++dis){
      cout << "collision" << dis->first << "number" << dis->second << endl;
    }
        return 0;
}