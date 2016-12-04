//使用local读取字符并打印
#include <iostream>
#include <locale>
#include <exception>
#include <cstdlib>
using namespace std;

int main(int argc, char const *argv[])
{
	try{
		//use classic C locale to write data to standard output
		cin.imbue(locale::classic());
		//use a German locale to write data to standard output
		//-use different locale names for windows and POSIX
		#ifdef _MSC_VER
			cout.imbue(locale("deu_deu.1252"));
		#else
			cout.imbue(locale("de_DE"));
		#endif
		//read and output floating-point values in aloop
		cout << "input floating-point values(classic notation): "
			 << endl;
		double value;
		while(cin >> value){
			cout << value << endl;
		}
	}catch(const std::exception& e){
		cerr << "Exception: " << e.what() << endl;
		return EXIT_FAILURE;
	}
	return 0;
}