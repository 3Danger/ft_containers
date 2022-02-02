#include "vector.hpp"
#include <string>
#include <vector>
#include <iostream>

//void	print(ft::vector<std::string> & vec){
//	ft::vector<std::string>::iterator start = vec.begin();
//	ft::vector<std::string>::iterator finish = vec.end();

//	while(start != finish){
//		std::cout << *start << std::endl;
//		start++;
//	}
//}

//int main(){
//	std::string str = "123456789";
//	std::string str2 = "ABCDEF";
//	ft::vector<std::string> fvstr;
//	std::vector<std::string> svstr;
//	for (size_t i = 0; i < 10; i++)
//		fvstr.push_back("hello_" + std::to_string(i));
//	print(fvstr);
//	for (size_t i = 0; i < 10; i++)
//		svstr.push_back("hello_" + std::to_string(i));
//}


//std::cout << *fvstr.begin() << std::endl;
//	fvstr.resize(5);
//std::cout << *fvstr.begin() << std::endl;
//	fvstr.resize(3);
//	fvstr.resize(8);
//	fvstr.resize(2);

//	svstr.resize(5);
//	svstr.resize(3);
//	svstr.resize(8);
//	svstr.resize(2);
//}

//int main(){
//	ft::vector<int> fvstr;
//	std::vector<int> svstr;
//	for (size_t i = 0; i < 10; i++)
//		fvstr.push_back(i);
//	for (size_t i = 0; i < 10; i++)
//		svstr.push_back(i);


//std::cout << *fvstr.begin() << std::endl;
//	fvstr.resize(5);
//std::cout << *fvstr.begin() << std::endl;
//	fvstr.resize(3);
//	fvstr.resize(8);
//	fvstr.resize(2);

//	svstr.resize(5);
//	svstr.resize(3);
//	svstr.resize(8);
//	svstr.resize(2);
//}



#include <iostream>
#include <string>
   #include "vector.hpp"
#include <vector>


//#define STD

#ifdef STD
    //namespace ft = std
	#define ft std
#endif

typedef struct    s_data
{
    void    *content;
}                t_data;

template<typename T>
void print_struct_vector(T &Vec, std::string const & str)
{
    std::cout << std::endl;
    std::cout << str <<" values (std::string*): ";
    for (size_t i = 0; i < Vec.size(); i++)
        std::cout << *(std::string *)(Vec[i].content) << " ";
    std::cout << std::endl;
    std::cout << ".size(): " << Vec.size() << std::endl;
    std::cout << ".capacity(): " << Vec.capacity() << std::endl;
    std::cout << std::endl;
}

template<typename T>
void print_vector(T &Vec, std::string const & str)
{
    std::cout << std::endl;
    std::cout << str <<" values: ";
    for (size_t i = 0; i < Vec.size(); i++)
        std::cout << Vec[i] << " ";
    std::cout << std::endl;
    std::cout << ".size(): " << Vec.size() << std::endl;
    std::cout << ".capacity(): " << Vec.capacity() << std::endl;
    std::cout << std::endl;
}

int main()
{

	ft::vector<int> intVec;
	for (size_t i = 0; i < 10; i++)
	{
		if (i <= 5 || i >= 8)
			intVec.push_back(i);
		std::cout << "----------------\n";
	}

	intVec.resize(13);
    for(uint i = 0; i < intVec.size(); ++i)
        intVec[i] = i;
    print_vector(intVec, "intVec");
    while (intVec.size())
        intVec.erase(intVec.end()-1);
    print_vector(intVec, "intVec");
    while (intVec.size() < 10)
        intVec.push_back(9);
    print_vector(intVec, "intVec");
    while (intVec.size())
        intVec.erase(intVec.begin());
    print_vector(intVec, "intVec");
	

    // std::cout <<"###################################################################" << std::endl;
    // std::cout << "###\t\t\t\tVECTOR\t\t\t\t###" << std::endl;
    // std::cout << "###################################################################\n" << std::endl;

    // std::cout << "\t\tdefault constructor\tvector()" << std::endl;
    // ft::vector<int> intVec;
    // ft::vector<std::string> strVec;
    // ft::vector<t_data> structVec;
    // print_vector(intVec, "intVec");
    // print_vector(strVec, "strVec");
    // print_struct_vector(structVec, "structVec");
    // std::cout << "intVec.empty() : " << intVec.empty() << std::endl;
    // std::cout << "strVec.empty() : " << strVec.empty() << std::endl;
    // std::cout << "structVec.empty() : " << structVec.empty() << std::endl << std::endl;

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\tfilling constructor\tvector( size_t n, const_reference value )\n" << std::endl;
    // std::cout << "\t\t\tintVec2( 5, 3 )" << std::endl;
    // ft::vector<int> intVec2(5, 3);
    // print_vector(intVec2, "intVec2");
    // std::cout << "\t\t\tstrVec2( 5, \"Str\" )" << std::endl;
    // ft::vector<std::string> strVec2(5, "Str");
    // print_vector(strVec2, "strVec2");
    // std::cout << "\t\t\tstructVec2( 5, t_data )" << std::endl;
    // t_data    data;
    // data.content = new std::string("content");
    // ft::vector<t_data> structVec2(5, data);
    // print_struct_vector(structVec2, "structVec2");
    // std::cout << "intVec2.empty() : " << intVec2.empty() << std::endl;
    // std::cout << "strVec2.empty() : " << strVec2.empty() << std::endl;
    // std::cout << "structVec2.empty() : " << structVec2.empty() << std::endl;

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\trange constructor vector( vector(InputIt first, InputIt last )\n" << std::endl;
    // std::cout << "\t\tintVec3( ++intVec2.begin(), --intVec2.end() )" << std::endl;
    // ft::vector<int> intVec3(++intVec2.begin(), --intVec2.end());
    // print_vector(intVec3, "intVec3");
    // std::cout << "\t\tstrVec3( ++strVec2.begin(), --strVec2.end() )" << std::endl;
    // ft::vector<std::string> strVec3(++strVec2.begin(), --strVec2.end());
    // print_vector(strVec3, "strVec3");
    // std::cout << "\t\tstructVec3( ++structVec2.begin(), --structVec2.end() )" << std::endl;
    // ft::vector<t_data> structVec3(++structVec2.begin(), --structVec2.end());
    // print_struct_vector(structVec3, "structVec3");

    // std::cout << "intVec2 < intVec3  : " << (intVec2 < intVec3) << " | strVec3 < strVec2 : " << (strVec3 < strVec2) << std::endl;

	// print_vector(intVec2, "intVec2");
	// print_vector(intVec3, "intVec3");
    // std::cout << "intVec2 <= intVec3 : " << (intVec2 <= intVec3) << " | strVec3 <= strVec2 : " << (strVec3 <= strVec2) << std::endl;
	// print_vector(strVec3, "strVec3");
	// print_vector(intVec3, "intVec3");
    // std::cout << "intVec2 > intVec3  : " << (intVec2 > intVec3)<< " | strVec3 > strVec2 : " << (strVec3 > strVec2) << std::endl;
    // std::cout << "intVec2 >= intVec3 : " << (intVec2 >= intVec3)<< " | strVec3 >= strVec2 : " << (strVec3 >= strVec2) << std::endl;
    // std::cout << "intVec2 == intVec3 : " << (intVec2 == intVec3)<< " | intVec3 == intVec2 : " << (strVec3 == strVec2) << std::endl;
    // std::cout << "intVec2 != intVec3 : " << (intVec2 != intVec3)<< " | strVec3 != strVec2 : " << (strVec3 != strVec2) << std::endl;

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\tcopy constructor vector( const vector &other )\n" << std::endl;
    // std::cout << "\t\t\tintVec4( intVec2 )" << std::endl;
    // ft::vector<int> intVec4(intVec2);
    // print_vector(intVec4, "intVec4");
    // std::cout << "\t\t\tstrVec4( strVec2 )" << std::endl;
    // ft::vector<std::string> strVec4(strVec2);
    // print_vector(strVec4, "strVec4");
    // std::cout << "\t\t\tstructVec4( structVec2 )" << std::endl;
    // ft::vector<t_data> structVec4(structVec2);
    // print_struct_vector(structVec4, "structVec4");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t\t.max_size()\n" << std::endl;
    // std::cout << "intVec.max_size() : " << intVec.max_size() << std::endl << std::endl;
    // std::cout << "strVec.max_size() : " << strVec.max_size() << std::endl << std::endl;
    // std::cout << "structVec.max_size() : " << structVec.max_size() << std::endl << std::endl;

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t\t.resize( size_t n )" << std::endl;
    // //free(data.content);
    // //data.content = new int(42);
    // for (size_t i = 0; i < 10; i++)
    // {
    //     int rndmdNbr = rand() % 10;
    //     intVec.push_back(rndmdNbr);
    //     strVec.push_back("Str-" + std::to_string(rndmdNbr));
    //     structVec.push_back(data);
    // }
    // std::cout << std::endl;
    // print_vector(intVec, "intVec");
    // print_vector(strVec, "strVec");
    // print_struct_vector(structVec, "structVec");
    // std::cout << "\t\t\t.resize( 10 ) " << std::endl;
    // intVec.resize(10);
    // strVec.resize(10);
    // structVec.resize(10);
    // print_vector(intVec, "intVec");
    // print_vector(strVec, "strVec");
    // print_struct_vector(structVec, "structVec");
    // std::cout << "\t\t\t.resize( 5 ) " << std::endl;
    // intVec.resize(5);
    // strVec.resize(5);
    // structVec.resize(5);
    // print_vector(intVec, "intVec");
    // print_vector(strVec, "strVec");
    // print_struct_vector(structVec, "structVec");
    // std::cout << "\t\t.resize( size_t n, const_reference value )\n" << std::endl;
    // intVec.resize(7, -1);
    // std::cout << "\t\t\tintVec.resize( 7, -1 )" << std::endl;
    // print_vector(intVec, "intVec");
    // strVec.resize(7, "value");
    // std::cout << "\t\t\tstrVec.resize( 7, \"value\" )" << std::endl;
    // print_vector(strVec, "strVec");
    // t_data    data2;
    // data2.content = new int(35);
    // structVec.resize(7, data2);
    // std::cout << "\t\t\tstructVec.resize( 7, *some stuct* )" << std::endl;
    // print_struct_vector(structVec, "structVec");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t\t.reserve( size_t n )\n" << std::endl;
    // std::cout << "\t\t\tintVec.reserve( 100 )  " << std::endl;
    // intVec.reserve(100);
    // print_vector(intVec, "intVec");
    // std::cout << "\t\t\tstrVec.reserve( 100 )  " << std::endl;
    // strVec.reserve(100);
    // print_vector(strVec, "strVec");
    // std::cout << "\t\t\tstructVec.reserve( 100 )  " << std::endl;
    // structVec.reserve(100);
    // print_struct_vector(structVec, "structVec");
    // std::cout << "\t\t\tintVec.reserve( 10 )  " << std::endl;
    // intVec.reserve(10);
    // print_vector(intVec, "intVec");
    // std::cout << "\t\t\tstrVec.reserve( 10 )  " << std::endl;
    // strVec.reserve(10);
    // print_vector(strVec, "strVec");
    // std::cout << "\t\t\tstructVec.reserve( 10 )  " << std::endl;
    // structVec.reserve(10);
    // print_struct_vector(structVec, "structVec");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t\t.front()" << std::endl;
    // std::cout << "intVec.front() : " << intVec.front() << std::endl << std::endl;
    // std::cout << "strVec.front() : " << strVec.front() << std::endl << std::endl;
    // std::cout << "(char*)structVec.front().content : " << (char*)structVec.front().content << std::endl << std::endl;

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t\t.back()" << std::endl;
    // std::cout << ".intVec.back() : " << intVec.back() << std::endl << std::endl;
    // std::cout << ".strVec.back() : " << strVec.back() << std::endl << std::endl;
    // std::cout << "(char*)structVec.back().content : " << (char*)structVec.back().content << std::endl << std::endl;

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t\t.at( size_type n )" << std::endl;
    // try {
    //     std::cout << "intVec.at( 3 ) : " << intVec.at(3) << std::endl;
    //     std::cout << "intVec.at( 13 ) : " << intVec.at(13) << std::endl << std::endl;
    // } catch (std::exception &e) {
    //     std::cerr << e.what() << std::endl << std::endl;
    // }
    // try {
    //     std::cout << "strVec.at( 3 ) : " << strVec.at(3) << std::endl;
    //     std::cout << "strVec.at( 13 ) : " << strVec.at(13) << std::endl << std::endl;
    // } catch (std::exception &e) {
    //     std::cerr << e.what() << std::endl << std::endl;
    // }
    // try {
    //     std::cout << "(char*)structVec.at( 5 ).content : " << (char*)structVec.at(5).content << std::endl;
    //     std::cout << "(char*)structVec.at( 13 ).content : " << (char*)structVec.at(13).content << std::endl << std::endl;
    // } catch (std::exception &e) {
    //     std::cerr << e.what() << std::endl << std::endl;
    // }

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t.assign( InputIt first, InputIt last )" << std::endl;
    // ft::vector<int> intVec5(5, 1);
    // ft::vector<std::string> strVec5(5, "Str");
    // ft::vector<t_data> structVec5(5, data2);
    // print_vector(intVec5, "intVec5");
    // print_vector(strVec5, "strVec5");
    // print_struct_vector(structVec5, "structVec5");
    // intVec5.assign(++intVec.begin(), --intVec.end());
    // strVec5.assign(++strVec.begin(), --strVec.end());
    // structVec5.assign(++structVec.begin(), --structVec.end());
    // std::cout << "\tintVec5.assign( ++intVec.begin(), --intVec.end() )" << std::endl;
    // print_vector(intVec5, "intVec5");
    // std::cout << "\tstrVec5.assign( ++strVec.begin(), --strVec.end() )" << std::endl;
    // print_vector(strVec5, "strVec5");
    // std::cout << "\tstructVec5.assign( ++structVec.begin(), --structVec.end() )" << std::endl;
    // print_struct_vector(structVec5, "structVec5");
    // std::cout << "\t.assign( size_t n, const_reference value )" << std::endl;
    // intVec5.assign(6, 1);
    // strVec5.assign(6, "newStr");
    // structVec5.assign(6, data2);
    // std::cout << "\n\t\tintVec5.assign( 6, 1 )\n";
    // print_vector(intVec5, "intVec5");
    // std::cout << "\n\t\tstrVec5.assign( 6, \"newStr\" )\n";
    // print_vector(strVec5, "strVec5");
    // std::cout << "\n\t\tstructVec5.assign( 6, *some struct* )\n";
    // print_struct_vector(structVec5, "structVec5");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t\t.pop_back()" << std::endl;
    // print_vector(intVec, "intVec");
    // print_vector(strVec, "strVec");
    // print_struct_vector(structVec, "structVec");
    // std::cout << "\t\t\tintVec.pop_back()" << std::endl;
    // intVec.pop_back();
    // print_vector(intVec, "intVec");
    // std::cout << "\t\t\tstrVec.pop_back()" << std::endl;
    // strVec.pop_back();
    // print_vector(strVec, "strVec");
    // std::cout << "\t\t\tstructVec.pop_back()" << std::endl;
    // structVec.pop_back();
    // print_struct_vector(structVec, "structVec");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t.push_back( const_reference value )" << std::endl;
    // std::cout << "\n\t\tintVec.push_back( 42 )\n";
    // intVec.push_back(42);
    // print_vector(intVec, "intVec");
    // std::cout << "\n\t\tstrVec.push_back( \"newStr\" )\n";
    // strVec.push_back("newStr");
    // print_vector(strVec, "strVec");
    // std::cout << "\n\t\tstructVec.push_back( *some struct* )\n";
    // structVec.push_back(data);
    // print_struct_vector(structVec, "structVec");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t.insert( iterator pos, const_reference value )" << std::endl;
    // intVec.insert(++intVec.begin(), 69);
    // strVec.insert(++strVec.begin(), "Insert");
    // structVec.insert(++structVec.begin(), data2);
    // std::cout << "\n\t\tintVec.insert( ++intVec.begin(), 69 )\n";
    // print_vector(intVec, "intVec");
    // std::cout << "\n\t\tstrVec.insert( ++strVec.begin(), \"Insert\" )\n";
    // print_vector(strVec, "strVec");
    // std::cout << "\n\t\tstructVec.insert( ++structVec.begin(), *some struct* )\n";
    // print_struct_vector(structVec, "structVec");
    // std::cout << "\t.insert( iterator pos, size_t count, const_reference value )" << std::endl;
    // intVec.insert(--intVec.end(), 2, 69);
    // strVec.insert(--strVec.end(), 2, "Insert");
    // structVec.insert(--structVec.end(), 2, data2);
    // std::cout << "\n\t\tintVec.insert( --intVec.end(), 2, 69 )\n";
    // print_vector(intVec, "intVec");
    // std::cout << "\n\t\tstrVec.insert( --strVec.end(), 2, \"Insert\" )\n";
    // print_vector(strVec, "strVec");
    // std::cout << "\n\t\tstructVec.insert( --structVec.end(), 2, *some struct* )\n";
    // print_struct_vector(structVec, "structVec");
    // std::cout << "\tinsert( iterator pos, InputIt first, InputIt last )" << std::endl;
    // intVec.insert(intVec.begin() + 5, ++intVec5.begin(), --intVec5.end());
    // strVec.insert(strVec.begin() + 5, ++strVec5.begin(), --strVec5.end());
    // structVec.insert(structVec.begin() + 5, ++structVec5.begin(), --structVec5.end());
    // std::cout << "\n\t\tintVec.insert(intVec.begin() + 5, ++intVec5.begin(), --intVec5.end())\n";
    // print_vector(intVec, "intVec");
    // std::cout << "\n\t\tstrVec.insert(strVec.begin() + 5, ++strVec5.begin(), --strVec5.end())\n";
    // print_vector(strVec, "strVec");
    // std::cout << "\n\t\tstructVec.insert(structVec.begin() + 5, ++structVec5.begin(), --structVec5.end())\n";
    // print_struct_vector(structVec, "structVec");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t.erase( iterator pos )" << std::endl;
    // intVec.erase(++intVec.begin());
    // strVec.erase(++strVec.begin());
    // structVec.erase(++structVec.begin());
    // std::cout << "\n\t\tintVec.erase( ++intVec.begin() )\n";
    // print_vector(intVec, "intVec");
    // //std::cout << "\n\t\tstrVec.erase( ++strVec.begin() )\n";
    // print_vector(strVec, "strVec");
    // //std::cout << "\n\t\tstructVec.erase( ++structVec.begin() )\n";
    // print_struct_vector(structVec, "structVec");
    // //std::cout << "\t\t.erase( iterator first, iterator last )" << std::endl;
    // //intVec.erase(++intVec.begin(), --intVec.end());
    // //strVec.erase(++strVec.begin(), --strVec.end());
    // //structVec.erase(++structVec.begin(), --structVec.end());
    // //std::cout << "\n\t\tintVec.erase( ++intVec.begin(), --intVec.end() )\n";
    // print_vector(intVec, "intVec");
    // //std::cout << "\n\t\tstrVec.erase( ++strVec.begin(), --strVec.end() )\n";
    // print_vector(strVec, "strVec");
    // //std::cout << "\n\t\tstructVec.erase( ++structVec.begin(), --structVec.end() )\n";
    // print_struct_vector(structVec, "structVec");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t.swap( vector &other )\n" << std::endl;
    // ft::vector<int> swapIntVec;
    // ft::vector<std::string> swapStrVec;
    // for (int i = 0; i < 5; i++)
    // {
    //     int rndmdNbr = rand() % 10;
    //     swapIntVec.push_back(rndmdNbr);
    //     swapStrVec.push_back("Str-" + std::to_string(rndmdNbr));
    // }
    // std::cout << "\t\tVectors for swap" << std::endl;
    // print_vector(swapIntVec, "swapIntVec");
    // print_vector(swapStrVec, "swapStrVec");
    // print_struct_vector(structVec2, "swapStructVec");
    // intVec.swap(swapIntVec);
    // strVec.swap(swapStrVec);
    // structVec.swap(structVec2);
    // std::cout << "\t\tVector after intVec.swap( swapIntVec )" << std::endl;
    // print_vector(intVec, "intVec");
    // print_vector(swapIntVec, "swapIntVec");
    // std::cout << "\t\tVector after strVec.swap( swapStrVec )" << std::endl;
    // print_vector(strVec, "strVec");
    // print_vector(swapStrVec, "swapStrVec");
    // std::cout << "\t\tVector after structVec.swap( swapStructVec )" << std::endl;
    // print_struct_vector(structVec, "structVec");
    // print_struct_vector(structVec2, "swapStructVec");

    // std::cout << "<+======================================================================+>\n" << std::endl;

    // std::cout << "\t\t.clear()" << std::endl;
    // intVec.clear();
    // strVec.clear();
    // structVec.clear();
    // print_vector(intVec, "intVec");
    // print_vector(strVec, "strVec");
    // print_struct_vector(structVec, "structVec");

    // free(data.content);
    // free(data2.content);
    return 0;
}
