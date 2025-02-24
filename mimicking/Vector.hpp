#ifndef Vector_h
#define Vector_h

using len_type = unsigned int; // instead of this we could use size_t, this is a default type in c++ that is unsigned int type and the actual size of size_t depends on the sys arch. it adjusts accordingly. so platform independent. generally used when dealing with ranges, mem allocations etc.
template <typename T>
class Vector{
private:
    len_type len;
    len_type curr_max_len;
    const int defualt_len = 5;
    T *arr;
    
public:

    //default constructor
    Vector(){

        arr = new T[defualt_len]; // Allocating in the heap.
        curr_max_len = defualt_len;
        len = 0;
    }
    //parametrized constructor
    Vector(len_type n, const T &val){
        arr = new T[n];
        for(int i = 0; i < n; i++){
            arr[i] = val;
        }
        len = n;
        curr_max_len = n;
    }
    // copy constructor
    Vector(const Vector &vec){
        arr = new T(vec.curr_max_len);
        len = vec.len;
        curr_max_len = vec.curr_max_len;
        for(int i=0; i < len; i++){
            arr[i] = vec[i];
        }
    }
    

    void push_back(const T &val){

        if(len < curr_max_len){
            arr[len] = val;
            len++;
        }
        else{
            //try expanding the capacity of the vector
            T *temp = new T[curr_max_len * 2];
            for(int i = 0; i < len; i++){
                temp[i] = arr[i];
            }
            temp[len] = val;

            delete[] arr;
            arr = temp;
            len = len + 1;
            curr_max_len *= 2;
            // delete[] temp;
        }

    }
    void pop_back(){
        if(len > 0){
        len--;
        }
        // check if we have to reduce the curr_max_len
        if(len == curr_max_len / 2 && curr_max_len / 2 >= 5){
            T *temp = new T[curr_max_len / 2];
            for (int i =0; i < len; i++){
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            curr_max_len = curr_max_len / 2;
        }
    }
    void del(len_type ind){
        if(ind < len){
            for(int i = ind; i < len; i++){
                arr[i] = arr[i+1];
            }
            len--;
        }
        //check if we need to reduce the curr_max_len
        if(len == curr_max_len / 2 ){
            T *temp = new T[curr_max_len / 2];
            for (int i =0; i < len; i++){
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            curr_max_len = curr_max_len / 2;
        }

    }

    void insert(len_type pos,const T& val){
        // push back some value at the end ==> this is to check if we can expand for one element. and then overwrite while shifting the elements from pos.
        if(pos < len){
            push_back(val);
            for(int i = len-1; i > pos; i--){
                arr[i+1] = arr[i];
            }
        }
        else{
            throw std::out_of_range("Insert is requested at out of range");
        }

    }
    void clear(){
        delete[] arr;
        arr = nullptr;
        len = 0;
        curr_max_len = defualt_len;
    }

    len_type length(){
        return this->len;
    }
    len_type curr_max_length(){
        return curr_max_len;
    }
    bool is_empty(){
        return len == 0;
    }


    T& operator [](len_type pos) {
        if(pos < len){
            return arr[pos];
        }
        // the [] does not do range checks, hence i have an explicit check. we can use .at(i) as an alternative which does have range check.
    }
    
    Vector& operator = (Vector &vec){
        delete[] arr;
        arr = new T[vec.curr_max_len];
        for(int i=0; i<len;i++){
            arr[i] = vec[i];
        }
        this->len = vec.len;
        this->curr_max_len = vec.curr_max_len;

        return *this;
    }


    ~Vector(){
        delete[] arr;
    }



};


#endif
