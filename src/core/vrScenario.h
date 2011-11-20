#ifndef VRSCENARIO_H_
#define VRSCENARIO_H_

#include <core/vrMusic.h>
#include <string>
using std::string;

typedef struct _GameImage {
	string imageFilename;
	int leftOffset;
} GameImage;

class VRScenario {
private:
	string description;
	string irrFile;
	TrackType instrument;
	GameImage guitarra;
	GameImage notas[5];
	int offset_colisao_notas;
	int offset_topo_aperto_botao;
	int erro1_offset_topo_aperto_botao;
	int erro2_offset_topo_aperto_botao;
public:
	VRScenario(string file);
	virtual ~VRScenario();

	inline string getIrrFile() {
		return irrFile;
	}
	inline GameImage getGuitarra() {
		return guitarra;
	}
	inline GameImage getNotas(int i) {
		return notas[i];
	}
	inline int getOffsetColisaoNotas(){
		return offset_colisao_notas;
	}
	inline int getOffsetTopoApertoBotao() {
		return offset_topo_aperto_botao;
	}
	inline int getErro1OffsetTopoApertoBotao() {
		return erro1_offset_topo_aperto_botao;
	}
	inline int getErro2OffsetTopoApertoBotao() {
		return erro2_offset_topo_aperto_botao;
	}
};

#endif /*VRSCENARIO_H_*/
