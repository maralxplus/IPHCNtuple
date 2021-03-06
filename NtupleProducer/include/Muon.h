#ifndef MUON_H
#define MUON_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Base.h"

class Muon : public Base
{
    public:

        Muon();
        virtual ~Muon();

        static bool sortPtPredicate(Muon lhs, Muon rhs)  {return (lhs.pt() > rhs.pt());};

        int ID()                                         {return _ID;};

        void setFakeType(int faketype)                   {_fakeType = faketype;};
        int fakeType()                                   {return _fakeType;};

        bool sel();
        void read();
        void init();

        // General informations
        float E()                  {return _E;};
        float pt()                 {return _pt;};
        float eta()                {return _eta;};
        float phi()                {return _phi;};
        float m()                  {return _m;};
        int charge()               {return _charge;};
        int id()                   {return _id;};

        // Id
        bool isLoose()             {return _isLoose;};  
	bool isMedium()            {return _isMedium;};
        bool isTight()             {return _isTight;};
        bool isPFMuon()            {return _isPFMuon;};
     
        bool isLooseTTH()          {return _isLooseTTH;};
        bool isFakeableTTH()       {return _isFakeableTTH;};
        bool isTightTTH()          {return _isTightTTH;};

        // Variables for Id
        float dxy()                {return _dxy;};
        float dz()                 {return _dz;};
        float iso()                {return _iso;};
        float sip3d()              {return _sip3d;};
        float bestTrackpt()        {return _bestTrack_pt;};
        float bestTrackptError()   {return _bestTrack_ptError;};
        //float dB3D()               {return _dB3D;};
        //float edB3D()              {return _edB3D;};
	
        // MVA
        float lepMVA()             {return _lepMVA;};
        float lepMVA_Moriond16()   {return _lepMVA_Moriond16;};
        	
	float lepMVA_miniRelIsoCharged()    {return _lepMVA_miniRelIsoCharged;};
        float lepMVA_miniRelIsoNeutral()    {return _lepMVA_miniRelIsoNeutral;};
        float lepMVA_jetPtRelv2()           {return _lepMVA_jetPtRelv2;};
        //float lepMVA_jetDR()         	    {return _lepMVA_jetDR;};
        float lepMVA_jetPtRatio()    	    {return _lepMVA_jetPtRatio;};
        float lepMVA_jetBTagCSV()    	    {return _lepMVA_jetBTagCSV;};
        float lepMVA_sip3d()         	    {return _lepMVA_sip3d;};
        float lepMVA_dxy()           	    {return _lepMVA_dxy;};
        float lepMVA_dz()            	    {return _lepMVA_dz;};
        float lepMVA_mvaId()         	    {return _lepMVA_mvaId;};
        float lepMVA_eta()                  {return _lepMVA_eta;};
        float lepMVA_jetNDauChargedMVASel() {return _lepMVA_jetNDauChargedMVASel;};
      
 
    protected:

        int _ID;

        int _fakeType;

        // General informations
        float _E;
        float _pt;
        float _eta;
        float _phi;
        float _m;
        int _charge;
        int _id;

        // Id
        bool _isLoose; 
	bool _isMedium;
        bool _isTight;
        bool _isPFMuon;
   
        bool _isLooseTTH;
        bool _isFakeableTTH;
        bool _isTightTTH;
      

        // Variables for Id
        float _dxy;
        float _dz;
        float _iso;
        float _sip3d;
        float _bestTrack_pt;
        float _bestTrack_ptError;
        //float _dB3D;
        //float _edB3D;

       
        // MVA
        float _lepMVA; 
	float _lepMVA_Moriond16;

        float _lepMVA_miniRelIsoCharged;
        float _lepMVA_miniRelIsoNeutral;
        float _lepMVA_jetPtRelv2;
        //float _lepMVA_jetDR;
        float _lepMVA_jetPtRatio;
	float _lepMVA_jetBTagCSV;
        float _lepMVA_sip3d;
        float _lepMVA_dxy;
        float _lepMVA_dz;
        float _lepMVA_mvaId;
        float _lepMVA_eta;
        float _lepMVA_jetNDauChargedMVASel;
       
   
        ClassDef(Muon,1)
};

#endif
