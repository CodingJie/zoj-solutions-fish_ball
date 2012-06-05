// 3004292 2008-07-25 13:18:54 Accepted 2158 C++ 00:00.53 880K 呆滞的慢板 

// 最小生成树 Prim 算法，注意邻接矩阵权要临时生成 

//////////////////////////////////////////////////////////
//       映射二分堆(Mapped_Binary_Heap)类模板 v1.0      //
//////////////////////////////////////////////////////////
//                                                      //
//                   模板参数                           //
// 1. SZ:     映射二分堆的最大索引号;                   //
// 2. T:      映射二分堆蕴含值类型，缺省为 int;         //
// 3. Op:     比较准则 functor，缺省为小于;             // 
//                                                      //
//                     接口                             //
// 1. clear:  清空堆;                                   //
// 2. empty:  判空;                                     // 
// 3. size:   返回堆大小(元素个数);                     //
// 4. top:    返回堆顶元素(索引和值结对);               //
// 5. push:   按索引插入元素，自动识别更新为最小值;     //
// 6. pop:    删除最小值;                               //
//                                                      //
//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////

#include <functional>
#include <iostream>
#include <algorithm>
using namespace std;

template <int SZ, class T = int, class Op = less<T> >
class MBH {
public:
    pair<int, T> heap[SZ + 1];
    int key[SZ + 1], sz;

public:

    void clear() { sz = 0; memset( key, 0, sizeof( key ) ); }
    
    int size() const { return sz; }
    
    bool empty() const { return sz == 0; } 
    
    pair<int, T> top() const { return heap[1]; }
    
    void push( int idx, T val ) {
        if( !key[idx] ) {
            key[idx] = ++sz;
            heap[sz] = make_pair( idx, val );
        }
        else if( Op()( val, heap[key[idx]].second ) )
            heap[key[idx]].second = val;
        for( int pos = key[idx], c;
            ( c = pos >> 1 ) && Op()( val, heap[c].second ); pos = c ) {
            swap( heap[pos], heap[c] );
            key[idx] = c;
            key[heap[pos].first] = pos;
        }
    }
    
    void pop() {
        key[heap[1].first] = 0;
        heap[1] = heap[sz--];
        if( sz == 0 )   return;
        key[heap[1].first] = 1;
        for( int pos = 1, c; ( c = pos<<1 ) <= sz; pos = c ) {
            if( c < sz && Op()( heap[c+1].second, heap[c].second ) ) ++c;
            if( Op()( heap[c].second, heap[pos].second ) ) {
                swap( heap[c], heap[pos] );
                key[heap[c].first] = c;
                key[heap[pos].first] = pos;
            }
            else break;
        }
    }

};

//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////

char    C[2001][7];

int     N,  x,  tot;

bool    B[2000];

MBH<2000> hp;

inline int dist( int i, int j ) {
    int ans = ( C[i][0] != C[j][0] );
    ans += ( C[i][1] != C[j][1] );
    ans += ( C[i][2] != C[j][2] );
    ans += ( C[i][3] != C[j][3] );
    ans += ( C[i][4] != C[j][4] );
    ans += ( C[i][5] != C[j][5] );
    ans += ( C[i][6] != C[j][6] );
    return  ans; 
}

int main() {

    while( scanf( "%d", &N ) && N ) {
        
        for( int i = 0; i < N; ++i )
            scanf( "%s", C[i] );
            
        hp.clear();
        
        tot = 0;
        
        memset( B, 0, sizeof( B ) );
        
        B[x = 0] = true;
        
        int cnt = N - 1;
        
        while( cnt-- ) {
            for( int i = 0; i < N; ++i )
                if( !B[i] ) hp.push( i, dist( x, i ) );
            B[x = hp.top().first] = true;
            tot += hp.top().second;
            hp.pop();
        }
        
        printf( "The highest possible quality is 1/%d.\n", tot );
        
    }
    

}
