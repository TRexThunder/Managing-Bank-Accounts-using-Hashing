#include "LinearProbing.h"

void merge2(std::vector<int> &v, int l, int m, int r) {
    int s1=m-l+1, s2=r-m;
    std::vector<int> v1, v2;
    for (int i=0; i<s1; i++) v1.push_back(v[l+i]);
    for (int i=0; i<s2; i++) v2.push_back(v[m+i+1]);
    int a=0, b=0, index=0;
    while (a<s1 || b<s2) {
        if (a>=s1) {
            v[l+index]=v2[b];
            index++;
            b++;
        }
        else if (b>=s2) {
            v[l+index]=v1[a];
            index++;
            a++;
        }
        else {
            if (v1[a]>=v2[b]) {
                v[l+index]=v1[a];
                index++;
                a++;
            }
            else {
                v[l+index]=v2[b];
                index++;
                b++;
            }
        }
    }
}

void msort2(std::vector<int> &v, int x, int y) {
    if (x<y) {
        int z=x+(y-x)/2;
        msort2(v, x, z);
        msort2(v, z+1, y);
        merge2(v, x, z, y);
    }
}

void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (first) {
        first=false;
        for (int i=0; i<142871; i++) {
            Account a;
            a.balance=-1;
            bankStorage1d.push_back(a);
        }
    }
    int counter=0;
    int hid=hash(id);
    while (true) {
        int current=(hid+counter)%142871;
        if (bankStorage1d[current].balance<0) {
            bankStorage1d[current].id=id;
            bankStorage1d[current].balance=count;
            break;
        }
        else counter++;
    }
    balances.push_back(count);
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    int bsz=balances.size();
    msort2(balances, 0, bsz-1);
    if (k>=bsz) return balances;
    else {
        std::vector<int> temp;
        for (int i=0; i<k; i++) temp.push_back(balances[i]);
        return temp;
    }
}

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (bankStorage1d.size()==0) return -1;
    int hid=hash(id);
    for (int i=0; i<142871; i++) {
        int h=(hid+i)%142871;
        if (bankStorage1d[h].balance==-1) return -1;
        else if (bankStorage1d[h].balance>0 && bankStorage1d[h].id==id) return bankStorage1d[h].balance;
        else if (bankStorage1d[h].balance==-2 && bankStorage1d[h].id==id) return -1;
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (bankStorage1d.size()==0) {
        createAccount(id, count);
        return;
    }
    int hid=hash(id);
    for (int i=0; i<142871; i++) {
        int h=(hid+i)%142871;
        if (bankStorage1d[h].balance==-1) {
            createAccount(id, count);
            return;
        }
        else if (bankStorage1d[h].balance>0 && bankStorage1d[h].id==id) {
            int index;
            for (int j=0; j<balances.size();j++) if (balances[j]==bankStorage1d[h].balance) index=j;
            balances[index]+=count;
            bankStorage1d[h].balance+=count;
            return;
        }
        else if (bankStorage1d[h].balance==-2 && bankStorage1d[h].id==id) {
            createAccount(id, count);
            return;
        }
    }
    createAccount(id, count);
    return;
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (bankStorage1d.size()==0) return false;
    int hid=hash(id);
    for (int i=0; i<142871; i++) {
        int h=(hid+i)%142871;
        if (bankStorage1d[h].balance==-1) return false;
        else if (bankStorage1d[h].balance>0 && bankStorage1d[h].id==id) return true;
        else if (bankStorage1d[h].balance==-2 && bankStorage1d[h].id==id) return false;
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (bankStorage1d.size()==0) return false;
    int hid=hash(id);
    for (int i=0; i<142871; i++) {
        int h=(hid+i)%142871;
        if (bankStorage1d[h].balance==-1) return false;
        else if (bankStorage1d[h].balance>0 && bankStorage1d[h].id==id) {
            int index;
            for (int j=0; j<balances.size();j++) if (balances[j]==bankStorage1d[h].balance) index=j;
            balances.erase(balances.begin()+index);
            bankStorage1d[h].balance=-2;
            return true;
        }
        else if (bankStorage1d[h].balance==-2 && bankStorage1d[h].id==id) return false;
    }
    return false;
}

int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return balances.size();
}

int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int num=0, current;
    long long multiplier=13;
    for (int i=0; i<id.size(); i++) {
        current=(((int)(id[i]))*(i+1)*(i+1)*(multiplier%142871)*240043)%142871;
        multiplier*=13;
        num+=current;
    }
    return num%142871;
}