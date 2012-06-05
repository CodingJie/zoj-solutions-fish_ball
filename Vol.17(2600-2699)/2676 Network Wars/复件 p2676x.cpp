//////////////////////////////////////////////////////
//              最大流(路径扩充) v1.0               //
///////////////////Documentation//////////////////////
//                                                  //
// 1. SZ:       模板参数，确定最大的图规模;         //
// 2. init:     构建一个大小一定的空的流网络;       //
// 3. insert:   对流网络插入一条边;                 //
// 4. maxFlow:  求出指定源-汇的最大流值;            // 
//                                                  //
//////////////////////////////////////////////////////
//             2008 CopyRight(c) by elf             //
//////////////////////////////////////////////////////

#include <algorithm>
#include <vector>
using namespace std;

const double EPS = 1e-5;
const double INF = 1e300;

// 附带容差浮点比较 
inline bool eq( double x, double y ) { return x-y < EPS && y-x < EPS; }
inline bool ne( double x, double y ) { return x-y > EPS || y-x > EPS; }
inline bool gt( double x, double y ) { return x-y > EPS; }
inline bool ge( double x, double y ) { return y-x < EPS; }
inline bool lt( double x, double y ) { return y-x > EPS; }
inline bool le( double x, double y ) { return x-y < EPS; }

// 等于零、正数、负数、非负、非正、非零 
inline bool zr( double x ) { return x < EPS && x > -EPS; }
inline bool ps( double x ) { return x > EPS; }
inline bool ng( double x ) { return x < -EPS; }
inline bool nn( double x ) { return x > -EPS; }
inline bool np( double x ) { return x < EPS; }
inline bool nz( double x ) { return x > EPS || x < -EPS; }

struct Edge {
    int v, w;
    double f, c;
    Edge() {}
    Edge(int v, int w, double c, double f = 0)
        : v(v), w(w), c(c), f(f) {}
    int next(int vv) {return vv == v ? w : v;}
    double remain(int vv) {return vv == v ? c-f : f;}
    void increase(int vv, double val) {vv == v ? f += val : f -= val;}
};

template<int SZ, int BUF_SZ = SZ*SZ> 
class MaxFlow {
public:
    int size, edges;
    vector<Edge*> V[SZ+1];
    Edge buf[BUF_SZ];
    Edge* fwd[SZ+1];
    int Q[SZ + 1], top;
    
    double addFlow(int v, double flow) {
        if(fwd[v] == buf - 1) return flow;
        flow = min(flow, fwd[v]->remain(fwd[v]->next(v)));
        flow = min(flow, addFlow(fwd[v]->next(v), flow));
        fwd[v]->increase(fwd[v]->next(v), flow);
        return flow;
    }
    
    bool findPath(int s, int t) {
        memset(fwd, 0, sizeof(fwd));
        Q[0] = s;
        top = 1;
        fwd[s] = buf - 1;   // Sentinel
        while(top && !fwd[t]) {
            int pos = rand() % top;
            int v = Q[pos];
            swap(Q[pos], Q[--top]);
            for(int i = 0; i < V[v].size(); ++i) {
                if(!fwd[V[v][i]->next(v)] &&
                    V[v][i]->remain(v) > EPS) {
                    fwd[V[v][i]->next(v)] = V[v][i];
                    Q[top++] = V[v][i]->next(v);
                }
            }
        }
        return fwd[t] ? true : false;
    }
    
public:
    
    void init(int sz) {
        for(int i = 0; i <= size; ++i)
            V[i].clear();
        memset(fwd, 0, sizeof(fwd));
        size = sz;
        edges = 0;
    }
    
    void insert(int v, int w, double c) {
        buf[edges++] = Edge(v, w, c);
        V[v].push_back(buf + edges - 1);
        V[w].push_back(buf + edges - 1);
    } 
    
    double maxFlow(int s, int t) {
        for(int i = 0; i <= size; ++i)
            for(int j = 0; j < V[i].size(); ++j)
                V[i][j]->f = 0;
        double total = 0;
        while(findPath(s, t))
            total += addFlow(t, INF);
        return  total;
    }
    
};

//////////////////////////////////////////////////////
//             2008 CopyRight(c) by elf             //
//////////////////////////////////////////////////////

#include <iostream>
using namespace std;

MaxFlow<100, 400> mf;

int N, M, T = 0;

vector<int> EE;
bool B[101];

void dfs(int v) {
//    cout << v << ' ';
    B[v] = true;
    for(int i = 0; i < mf.V[v].size(); ++i) {
        if(!B[mf.V[v][i]->next(v)]) {
            if(mf.V[v][i]->remain(v) < EPS)
                EE.push_back(mf.V[v][i]-mf.buf);
            else dfs(mf.V[v][i]->next(v));
        }
    }
}

bool check(double lamda) {
    double ans;
    for(int i = 0; i < M; ++i) {
        mf.buf[i].c -= lamda;
        if(mf.buf[i].c < 0) ans += mf.buf[i].c;
    }
    ans += mf.maxFlow(1, N);
    for(int i = 0; i < M; ++i)
        mf.buf[i].c += lamda;
    return ans < 0;
}

int main() {
    while(cin >> N >> M) {
        if(T++) puts("");
        int v, w;
        double c, m = 0;
        mf.init(N);
        for(int i = 0; i < M; ++i) {
            cin >> v >> w >> c;
            m = max(m, c);
            mf.insert(v, w, c);
//            mf.insert(w, v, c);
        }
        double l = 0, r = m;
        while(r - l > EPS) {
            m = (l + r) / 2;
            if(check(m)) r = m;
            else l = m;
        }
/*
for(int i = 0; i < M; ++i) {
    cout << mf.buf[i].v << ' ';
    cout << mf.buf[i].w << ' ';
    cout << mf.buf[i].c << ' ';
    cout << mf.buf[i].f << endl;
}
*/
//cout << m << endl;
    memset(B, 0, sizeof(B));
    EE.clear();
    for(int i = 0; i < M; ++i) {
        mf.buf[i].c -= m;
        if(mf.buf[i].c < 0) EE.push_back(i);
    }
    dfs(1);puts("");
    sort(EE.begin(), EE.end());
    EE.resize(unique(EE.begin(), EE.end()) - EE.begin());
        cout << EE.size() << endl;
        for(int i = 0; i < EE.size(); ++i) {
            if(i) cout << ' ';
            cout << EE[i] + 1;
        }
    }
}
