#include "protos.h"
#include "tools.h"

void mainFuncao(int sim);

int main(int argc, char * argv[]) {
	int i, seed;
	for(i = 0; i < 10; i++){
		seed = -1089432789 + i*100000;
		setSeed(seed);
		mainFuncao(i+1);
	}
	return 0;
}

void mainFuncao(int sim){	
	int nneuron = 3129, i, j, nLs[5];
	int numConn = 0;
	float rescaleFac = 100.0, sizeNet = 2.0;
	unsigned char * typeList;
	connect * head, * mtxPre;
	char * baseName;

    nLs[0] = (int) round(sqrt(0.015*nneuron));
    nLs[1] = (int) round(sqrt(0.337*nneuron));
    nLs[2] = (int) round(sqrt(0.349*nneuron));
    nLs[3] = (int) round(sqrt(0.076*nneuron));
    nLs[4] = (int) round(sqrt(0.223*nneuron));
    
    nneuron = 0;
    for (i = 0; i < 5; i++)
   		nneuron += nLs[i]*nLs[i];	
	
	typeList = (unsigned char *) mallocc(nneuron*sizeof(unsigned char));
	head = createCortex (nneuron, rescaleFac, sizeNet, nLs, typeList);	
	baseName = "cortex";
	calcCluster(head, nneuron, baseName, sim);
	dijkstra(head, nneuron, baseName, sim);
	
	mtxPre = head->right;
	for (i = 0; i < nneuron; i++){
		numConn += mtxPre[i].length;
	}
	
	desalocar(head,nneuron);
	
	head = createRand(nneuron, numConn);
	baseName = "rand";
	calcCluster(head, nneuron, baseName, sim);
	dijkstra(head, nneuron, baseName, sim);
	
	desalocar(head,nneuron);
	
	head = createRegNet(nneuron, numConn);
	baseName = "reg";
	calcCluster(head, nneuron, baseName, sim);
	dijkstra(head, nneuron, baseName, sim);
	
	desalocar(head,nneuron);

	return;
}
