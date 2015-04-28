/*
 * CPlanet.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CPlanet.h"
#include <cmath>
using namespace std;

CPlanet::CPlanet() {
	m_par = NULL;
	m_ss = NULL;
	m_mass = -1;
	m_perihelion = -1;
	m_aphelion = -1;
	m_dynamics = CCoordSet();
	m_name = "uninitialized";
	m_angle = -1;
	cout << "ERROR: default constructor of CPlanet called\n";
	return;
}

CPlanet::CPlanet(vector<bool> flagforsatelliteuse) {
	//SURPRISE!
	m_par = NULL;
	m_ss = NULL;
	m_mass = -1;
	m_perihelion = -1;
	m_aphelion = -1;
	m_dynamics = CCoordSet();
	m_name = "uninitialized";
	m_angle = -1;
	return;
}

CPlanet::CPlanet(const CPlanet& rhs) {
	m_par = rhs.m_par;
	m_ss = rhs.m_ss;
	m_mass = rhs.m_mass;
	m_dynamics = rhs.m_dynamics;
	m_name = rhs.m_name;
	m_perihelion = rhs.m_perihelion;
	m_aphelion = rhs.m_aphelion;
	m_angle = rhs.m_angle;
}


CPlanet::CPlanet(float angle, float mass, float peri, float ap, CCoordSet ccs, string name, Par* par, CSolarSystem* ss) {
	m_ss = ss;
	m_par = par;
	m_mass = mass;
	m_dynamics = ccs;
	m_name = name;
	m_perihelion = peri;
	m_aphelion = ap;
	m_angle = angle;
}

CPlanet::~CPlanet() {

}

CPlanet CPlanet::operator=(const CPlanet& rhs)
{
	if(this == &rhs)
	        return *this;

	m_par = rhs.m_par;
	m_ss = rhs.m_ss;
	m_mass = rhs.m_mass;
	m_name = rhs.m_name;
	m_angle = rhs.m_angle;

	m_aphelion = rhs.m_aphelion; // furthest from sun
	m_perihelion = rhs.m_perihelion;
	m_dynamics = rhs.m_dynamics;

	return *this;
}

bool CPlanet::operator==(const CPlanet& rhs)
{
	return (m_name==rhs.m_name);
}

CSVector CPlanet::calcForce(CSolarSystem* ss){
	CSVector zero;
	return zero;
}

float CPlanet::calcEccentricity(){
	return 0;

}
void CPlanet::setDynamics(CCoordSet newSet){
	m_dynamics = newSet;
	if(m_dynamics.m_position.mag() > 100*m_aphelion){
		cout << "ERROR USING WORTHLESS APHELION FUNCTION\n";
		m_aphelion = m_dynamics.m_position.mag();
	} else if(m_dynamics.m_position.mag() < .8*m_perihelion){
		cout << "ERROR USING WORTHLESS APHELION FUNCTION\n";
		m_perihelion = m_dynamics.m_position.mag();
	}
	return;
}

float CPlanet::calcTheorVel()
{
	float a = (m_perihelion+m_aphelion)/2;
	if (a == 0) return 0;
	return sqrt(m_par->G*m_par->SolarMass*(2.0/m_dynamics.m_position.mag()-1.0/a));
}

