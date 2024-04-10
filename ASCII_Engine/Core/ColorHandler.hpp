#ifndef COLOR_HANDLER_HPP
#define COLOR_HANDLER_HPP

#include <string>

#include <vector>
#include <map>

#include "Cores_base.hpp"

class ColorHandler {
	
public:

	using MapaDeCores = std::vector< std::map<int,COR::Cor> >;

	ColorHandler(COR::Cor cor = COR::NULL_COLOR):cor(cor),altura(0),largura(0) {}
	ColorHandler(unsigned largura, unsigned altura, COR::Cor cor = COR::NULL_COLOR):
				largura(largura),altura(altura) { setCor(cor); }
				
	void setCor(COR::Cor cor) { this->cor = cor; clearMapaCores(); }
	COR::Cor getCorBase() const { return cor; }
	
	void pushCorLinha(unsigned front, unsigned end ) {mapaCores.push_back( { {front,cor}, {end,cor} } );}
	
	unsigned getAltura() const { return mapaCores.size(); }
	unsigned getLargura(unsigned l) const;
	
	//void mergeCores(const MapaDeCores &, unsigned, unsigned);
	void mergeCores(const ColorHandler &, unsigned, unsigned);
	
	const MapaDeCores &getMapaCores() const { return mapaCores; }
	
	std::string colorir(const std::string &, unsigned) const;
	
	void clearMapaCores();

private:
	COR::Cor cor; //cor base
	unsigned altura, largura; //altura e largura necessários?
	
	MapaDeCores mapaCores;
};

#endif