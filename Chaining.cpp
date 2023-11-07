#include "Chaining.h"

void merge1(std::vector<int> &v, int l, int m, int r) {
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

void msort1(std::vector<int> &v, int x, int y) {
    if (x<y) {
        int z=x+(y-x)/2;
        msort1(v, x, z);
        msort1(v, z+1, y);
        merge1(v, x, z, y);
    }
}


void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account a;
    a.id=id;
    a.balance=count;
    int h=hash(id);
    int sz=bankStorage2d.size();
    if (h>=sz) {
        for (int i=0; i<=h-sz; i++) {
            std::vector<Account> v;
            bankStorage2d.push_back(v);
        }
    }
    bankStorage2d[h].push_back(a);
    balances.push_back(count);
}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    int bsz=balances.size();
    msort1(balances, 0, bsz-1);
    if (bsz<=k) return balances;
    else {
        std::vector<int>temp;
        for (int i=0; i<k; i++) temp.push_back(balances[i]);
        return temp;
    }
}

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=hash(id), sz=bankStorage2d.size();
    if (h>=sz) return -1;
    else {
        int z=bankStorage2d[h].size();
        for (int i=0; i<z; i++) {
            Account current = bankStorage2d[h][i];
            if (current.id==id) return current.balance;
        }
        return -1;
    }
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int h=hash(id), sz=bankStorage2d.size();
    if (h>=sz) createAccount(id, count);
    else {
        int z=bankStorage2d[h].size();
        for (int i=0; i<z; i++) {
            Account current = bankStorage2d[h][i];
            if (current.id==id) {
                int index;
                for (int j=0; j<balances.size();j++) if (balances[j]==current.balance) index=j;
                balances[index]+=count;
                bankStorage2d[h][i].balance+=count;
                return;
            }
        }
        createAccount(id, count);
    }
    return;
}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=hash(id), sz=bankStorage2d.size();
    if (h>=sz) return false;
    else {
        int z=bankStorage2d[h].size();
        for (int i=0; i<z; i++) {
            Account current = bankStorage2d[h][i];
            if (current.id==id) return true;
        }
        return false;
    }
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=hash(id), sz=bankStorage2d.size();
    if (h>=sz) return false;
    else {
        int z=bankStorage2d[h].size();
        for (int i=0; i<z; i++) {
            Account current = bankStorage2d[h][i];
            if (current.id==id) {
                bankStorage2d[h].erase(bankStorage2d[h].begin()+i);
                int index;
                for (int j=0; j<balances.size();j++) if (balances[j]==current.balance) index=j;
                balances.erase(balances.begin()+index);
                return true;
            }
        }
        return false;
    }
}

int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return balances.size();
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int num=0;
    for (int i=0; i<id.size(); i++) num+=((7634+i*i)*static_cast<int>(id[i])*i)%4999;
    return num%4999;
}