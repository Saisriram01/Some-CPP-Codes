#include <iostream>
using namespace std;


template<typename T>
class sharedptr{
	private:
		T *res;
		int *counter;
		void incrementcounter(){
			if(counter)
				(*counter)++;
		}
		void decrementcounter(){
			if(counter)
				(*counter)--;
			if(*counter == 0)
				if(res)
				{	delete counter;
					delete res;
					res = nullptr;
					counter = nullptr;
				}
		}
	public:
		sharedptr (T *ptr = nullptr): res(ptr), counter(new int(1)){
			cout<<"constructor was called\n";
		}
		// copy constructor
		sharedptr(const sharedptr<T> &ptr){
			res = ptr.res;
			counter = ptr.counter;
			incrementcounter();

			cout<<"copy constructor was called\n";
		}
		// move copy constructor
		sharedptr(sharedptr<T> &&ptr){
			res = ptr.res;
			counter = ptr.counter;
			ptr.res = nullptr;
			ptr.counter = nullptr;

			cout<<"copy constructor was called\n";
		}
		// assignment operator
		sharedptr<T>& operator = (const sharedptr<T> &ptr){
			if(this != &ptr){
			this.res = nullptr;
			this->decrementcounter();
			this->res = ptr.res;
			this->counter = ptr.counter;
			this->incrementcounter();
		}
			return *this;
		}
		// move assignment operator
		sharedptr<T>& operator = (sharedptr<T> &&ptr){
			if(this != &ptr){
			this->decrementcounter();
			this->res = ptr.res;
			this->counter = ptr.counter;
			ptr.res = nullptr;
			ptr.counter = nullptr;
		}
			return *this;
		}
		void reset(T *ptr){
			decrementcounter();
			res = ptr;
			counter = new int(0);
			incrementcounter();
		}
		int get_count(){
			if(counter)
				return *counter;
			return -1;
		}
		T *operator->(){
			return res;
		}
		T& operator *(){

			return *res;
		}
		T* get(){
			return res;
		}
		~sharedptr(){
			decrementcounter();
		}

};


int main(){
	sharedptr<int> ptr1; // default constructor
	sharedptr<int> ptr2(new int(1)); // parameterised constructor
	sharedptr<int> ptr3(ptr2); // copy constructor
	sharedptr<int> ptr4(std::move(ptr1)); // move copy constructor
	ptr2 = std::move(ptr3); // move copy assignment operator

	ptr1.reset(new int(5));
	
	cout << (*ptr1); // * operator
	
	ptr1.get(); //raw pointer
	
	ptr1.get_count(); //number of objects pointing to the same resource


}
