Задача:     
Написать шаблон класс Array со следующей структурой:  

template < class T >  
class Array     
{       
	T array[size]; 
	public:     
		Array() {};     
		Array(T* b);        
		void show();        
		minimum(Array< T >& m);       
};
    

Описание методов:   
Array(T* b) - создает массив, копируя в него элементы b  
show() - выводит элементы массива в строке  
minimum(Array< T >& m) - возвращает самый маленький элемент массива m

Запуск на Bash:
Используя утилиту GNU make, запустить makefile, затем запустить файл program.