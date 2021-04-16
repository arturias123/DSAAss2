#include <stdio.h>
#include "main.h"
#include "Cache.h"
#include "Cache.cpp"

Data* getData(string s) {
	stringstream ss(s);
	int idata;
    float fdata;
    if (ss >> idata) 
		return new Int(idata);
    else if (ss >> fdata)
    	return new Float(fdata);
    else if (s.compare("true") || s.compare("false"))
    	return new Bool(s.compare("true"));
    else {
		s.resize(s.size()-1);
		return new Address(stoi(s));
	}
    	
}
void simulate(string filename,Cache* c)
{
  ifstream ifs;
  ifs.open(filename, std::ifstream::in);
  string s;
  while (getline(ifs, s))
  {
    stringstream ss(s);
    string code,tmp;
    ss >> code;
    int addr;
    switch (code[0]) {
    	case 'R': //read
			    ss >> addr; 
    			Data* res;
				res = c->read(addr);
    			if (res == NULL) {
    				ss >> tmp;
    				c->put(addr,getData(tmp));
    			} else {
					cout << res->getValue() << endl;
				}
    			break;
        case 'U': //put
                ss >> addr;
                ss >> tmp;
                c->put(addr,getData(tmp));
                break;
    	case 'W': //write
                ss >> addr;
    			ss >> tmp;
    			c->write(addr,getData(tmp));
    			break;
    	case 'P': // print
    			cout << "Print queue\n";
    			c->print();
    			break;
    	case 'E': // preorder
    			cout << "Print AVL in preorder\n";
    			c->preOrder();
    			break;
    	case 'I': // inorder
    			cout << "Print AVL in inorder\n";
    			c->inOrder();
    			break;
    }
  }
}
int main(int argc, char* argv[]) {
	//if (argc < 2)
    	//return 1;

	Cache* c = new Cache(MAXSIZE); 
  	//const char *fileName = argv[1];
    simulate("test1.txt",c);
  	delete c;
	return 0;
}
