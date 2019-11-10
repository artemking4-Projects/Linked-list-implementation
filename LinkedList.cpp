
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iterator>

using namespace std;

template<class T>
class ChainStep{
    
public:
    ChainStep() {}
    ChainStep(T* obj, ChainStep* p, ChainStep* n, int toEnd)
    {
        tillEnd = toEnd;
        pObject = obj;
        
        prev = p; 
        next = n;
    }
    
    bool hasNext(){
        return tillEnd != 0;
    }
    
    int tillEnd = 0;
    
    T* pObject = nullptr;
    
    ChainStep<T>* prev = nullptr;
    ChainStep<T>* next = nullptr;
};

ChainStep<char> AllocMessage(char* stuffe){
    int len = strlen(stuffe);
    
    ChainStep<char>* steps = (ChainStep<char>*)malloc(len * sizeof(ChainStep<char>));
    ChainStep<char>* p = 0;
    
    for(int i = 0; i < len; i++){
        auto step = (steps + (i * sizeof(ChainStep<char>)));
        auto n = (i + 1 > len) ? 0 : (steps + ((i + 1) * sizeof(ChainStep<char>)));
        
        char* thing = new char();
        *thing = stuffe[i];
        
        *step = ChainStep<char>(thing, p, n, len - i);
        p = step;
    }
        
    return *steps;
}

ChainStep<int> AllocInts(int* stuffe, int len){
    
    ChainStep<int>* steps = (ChainStep<int>*)malloc(len * sizeof(ChainStep<int>));
    ChainStep<int>* p = 0;
    
    for(int i = 0; i < len; i++){
        auto step = (steps + (i * sizeof(ChainStep<int>)));
        auto n = (i + 1 > len) ? 0 : (steps + ((i + 1) * sizeof(ChainStep<int>)));
        
        int* thing = new int();
        *thing = stuffe[i];
        
        *step = ChainStep<int>(thing, p, n, len - i);
        p = step;
    }
        
    return *steps;
}

int main()
{
    printf("---=== Ints ===---\n");
    
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ChainStep<int> ints = AllocInts(arr, 10);
    
    ChainStep<int> cur = ints;
    while(cur.hasNext()){
        printf("%d, ", *cur.pObject);
        cur = *cur.next;
    }
    printf("\n ---=== Chars ===---\n");
    
    ChainStep<char> chars = AllocMessage("yes daddy");
    
    ChainStep<char> curr = chars;
    while(curr.hasNext()){
        printf("%s", curr.pObject);
        curr = *curr.next;
    }


    return 0;
}