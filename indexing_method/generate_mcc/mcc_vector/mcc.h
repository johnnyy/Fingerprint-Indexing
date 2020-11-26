#ifndef MCC_H
#define MCC_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#ifndef PI
#define PI 3.1415926535897932384626433832795028841971693993751058209 
#endif


class Minu
{
public:
	int x;
	int y;
	float theta;
	int quality;
};

typedef vector<Minu> MinuList;

struct less_than_key
{
    inline bool operator() (const Minu& struct1, const Minu& struct2)
    {
        return (struct1.quality > struct2.quality);
    }
};


// load minutiae list from file
bool LoadMinutiaeList(const char* filename, MinuList& ML, int quantity_max_minutia);
bool LoadSourceAfisMinutiaeList(const char* filename, MinuList& ML, int threshold_quality);
bool LoadMCCMinutiaeList(const char* filename, MinuList& ML, int& width, int& height);

vector<vector<uint8_t>> getMCCBinVector(MinuList &ML, bool rotation, int R, int NS, int ND);

// get the local minutia
void ConstructLocalStructure(MinuList &ML, vector<MinuList> &LocalML, float R, bool Rotation=true);


static const double G_D[256] ={8.8077e-005,0.00010127,0.00011631,0.00013342,0.00015286,0.00017494,0.00019997,0.00022832,0.00026038,0.00029659,0.00033745,0.00038349,0.0004353,0.00049354,0.00055892,0.00063222,0.00071431,0.00080611,0.00090867,0.0010231,0.0011506,0.0012925,0.0014502,0.0016252,0.0018193,0.0020343,0.002272,0.0025346,0.0028242,0.0031434,0.0034946,0.0038807,0.0043044,0.004769,0.0052777,0.005834,0.0064416,0.0071043,0.0078264,0.0086121,0.0094659,0.010393,0.011397,0.012485,0.01366,0.01493,0.0163,0.017775,0.019361,0.021066,0.022895,0.024856,0.026953,0.029196,0.03159,0.034142,0.036859,0.039749,0.042817,0.046072,0.049519,0.053165,0.057018,0.061082,0.065364,0.069869,0.074603,0.079571,0.084778,0.090226,0.095921,0.10186,0.10806,0.1145,0.12121,0.12816,0.13537,0.14282,0.15053,0.15848,0.16668,0.17511,0.18377,0.19265,0.20175,0.21106,0.22055,0.23024,0.24009,0.2501,0.26025,0.27053,0.28092,0.2914,0.30195,0.31256,0.32321,0.33386,0.34451,0.35513,0.3657,0.37618,0.38657,0.39683,0.40694,0.41688,0.42662,0.43614,0.4454,0.4544,0.4631,0.47148,0.47952,0.4872,0.49449,0.50137,0.50783,0.51385,0.51941,0.52449,0.52907,0.53315,0.53672,0.53975,0.54225,0.5442,0.54561,0.54645,0.54675,0.54648,0.54565,0.54427,0.54234,0.53987,0.53686,0.53332,0.52926,0.52469,0.51963,0.5141,0.5081,0.50166,0.49479,0.48752,0.47986,0.47183,0.46347,0.45478,0.44579,0.43654,0.42703,0.4173,0.40737,0.39727,0.38701,0.37663,0.36615,0.35558,0.34497,0.33432,0.32366,0.31302,0.3024,0.29185,0.28136,0.27097,0.26068,0.25053,0.24051,0.23065,0.22096,0.21146,0.20215,0.19304,0.18415,0.17547,0.16703,0.15883,0.15087,0.14315,0.13568,0.12846,0.1215,0.11479,0.10833,0.10212,0.096169,0.090464,0.085005,0.079789,0.07481,0.070066,0.065551,0.06126,0.057187,0.053326,0.04967,0.046215,0.042952,0.039876,0.036979,0.034254,0.031695,0.029295,0.027046,0.024942,0.022976,0.021142,0.019432,0.01784,0.01636,0.014986,0.013713,0.012533,0.011442,0.010434,0.0095039,0.0086471,0.0078586,0.0071339,0.0064687,0.0058588,0.0053004,0.0047898,0.0043234,0.003898,0.0035104,0.0031577,0.0028372,0.0025463,0.0022827,0.0020439,0.0018281,0.0016331,0.0014573,0.0012989,0.0011563,0.0010282,0.0009133,0.00081026,0.00071802,0.00063554,0.00056188,0.00049618,0.00043765,0.00038558,0.0003393,0.00029824,0.00026184,0.00022961,0.00020111,0.00017595,0.00015375,0.0001342,0.00011699,0.00010187};
static const double G_D5[256] = {0.00015853,0.00018137,0.00020727,0.00023659,0.00026974,0.00030718,0.00034941,0.00039698,0.0004505,0.00051064,0.00057815,0.00065382,0.00073854,0.00083327,0.00093906,0.0010571,0.0011885,0.0013348,0.0014974,0.0016778,0.0018778,0.0020992,0.0023441,0.0026145,0.0029128,0.0032414,0.003603,0.0040003,0.0044365,0.0049146,0.005438,0.0060104,0.0066355,0.0073174,0.0080602,0.0088685,0.0097468,0.0107,0.011733,0.012852,0.014062,0.015368,0.016777,0.018295,0.019929,0.021683,0.023567,0.025585,0.027746,0.030056,0.032523,0.035154,0.037956,0.040937,0.044104,0.047464,0.051025,0.054793,0.058776,0.062981,0.067414,0.072081,0.076989,0.082144,0.08755,0.093213,0.099136,0.10532,0.11178,0.11851,0.12551,0.13278,0.14033,0.14816,0.15626,0.16462,0.17326,0.18216,0.19133,0.20074,0.21041,0.22032,0.23045,0.24081,0.25138,0.26215,0.2731,0.28422,0.2955,0.30692,0.31847,0.33012,0.34185,0.35365,0.3655,0.37738,0.38925,0.40111,0.41292,0.42467,0.43633,0.44787,0.45927,0.4705,0.48155,0.49238,0.50297,0.51329,0.52333,0.53305,0.54244,0.55147,0.56011,0.56835,0.57617,0.58354,0.59044,0.59687,0.60279,0.60821,0.61309,0.61743,0.62122,0.62445,0.6271,0.62918,0.63067,0.63157,0.63188,0.6316,0.63073,0.62927,0.62722,0.6246,0.6214,0.61764,0.61333,0.60847,0.60308,0.59718,0.59078,0.5839,0.57656,0.56876,0.56054,0.55192,0.54291,0.53354,0.52384,0.51382,0.5035,0.49293,0.48211,0.47107,0.45985,0.44845,0.43692,0.42527,0.41353,0.40171,0.38986,0.37798,0.36611,0.35426,0.34245,0.33071,0.31906,0.30751,0.29608,0.2848,0.27366,0.2627,0.25192,0.24135,0.23098,0.22083,0.21091,0.20123,0.1918,0.18263,0.17371,0.16506,0.15668,0.14857,0.14073,0.13316,0.12588,0.11886,0.11212,0.10565,0.099447,0.09351,0.087834,0.082414,0.077247,0.072326,0.067647,0.063202,0.058986,0.054992,0.051212,0.047641,0.044271,0.041095,0.038105,0.035294,0.032654,0.030179,0.027861,0.025692,0.023667,0.021777,0.020015,0.018376,0.016852,0.015438,0.014126,0.012912,0.011789,0.010751,0.0097937,0.0089117,0.0081,0.0073539,0.006669,0.0060411,0.0054661,0.0049402,0.0044599,0.0040217,0.0036224,0.0032591,0.0029289,0.0026291,0.0023573,0.0021112,0.0018886,0.0016875,0.0015062,0.0013427,0.0011957,0.0010635,0.0009448,0.00083841,0.00074313,0.00065793,0.00058182,0.00051391,0.00045341,0.00039957,0.00035171,0.00030922,0.00027155,0.00023819,0.00020868,0.00018262};
static const double G_S[301] = {0.042744,0.042014,0.041297,0.040592,0.039899,0.039218,0.038548,0.03789,0.037243,0.036607,0.035982,0.035368,0.034764,0.034171,0.033587,0.033014,0.03245,0.031896,0.031352,0.030817,0.030291,0.029773,0.029265,0.028766,0.028274,0.027792,0.027317,0.026851,0.026393,0.025942,0.025499,0.025064,0.024636,0.024215,0.023802,0.023396,0.022996,0.022604,0.022218,0.021838,0.021466,0.021099,0.020739,0.020385,0.020037,0.019695,0.019359,0.019028,0.018703,0.018384,0.01807,0.017762,0.017458,0.01716,0.016867,0.016579,0.016296,0.016018,0.015745,0.015476,0.015212,0.014952,0.014697,0.014446,0.014199,0.013957,0.013718,0.013484,0.013254,0.013028,0.012805,0.012587,0.012372,0.012161,0.011953,0.011749,0.011548,0.011351,0.011158,0.010967,0.01078,0.010596,0.010415,0.010237,0.010062,0.0098905,0.0097217,0.0095557,0.0093926,0.0092322,0.0090746,0.0089197,0.0087674,0.0086177,0.0084706,0.008326,0.0081839,0.0080441,0.0079068,0.0077718,0.0076391,0.0075087,0.0073805,0.0072545,0.0071307,0.007009,0.0068893,0.0067717,0.0066561,0.0065424,0.0064308,0.006321,0.0062131,0.006107,0.0060027,0.0059003,0.0057995,0.0057005,0.0056032,0.0055075,0.0054135,0.0053211,0.0052303,0.005141,0.0050532,0.0049669,0.0048821,0.0047988,0.0047169,0.0046363,0.0045572,0.0044794,0.0044029,0.0043277,0.0042539,0.0041812,0.0041099,0.0040397,0.0039707,0.0039029,0.0038363,0.0037708,0.0037064,0.0036432,0.003581,0.0035198,0.0034597,0.0034007,0.0033426,0.0032856,0.0032295,0.0031743,0.0031201,0.0030669,0.0030145,0.0029631,0.0029125,0.0028627,0.0028139,0.0027658,0.0027186,0.0026722,0.0026266,0.0025817,0.0025377,0.0024943,0.0024518,0.0024099,0.0023688,0.0023283,0.0022886,0.0022495,0.0022111,0.0021734,0.0021362,0.0020998,0.0020639,0.0020287,0.0019941,0.00196,0.0019266,0.0018937,0.0018613,0.0018296,0.0017983,0.0017676,0.0017374,0.0017078,0.0016786,0.00165,0.0016218,0.0015941,0.0015669,0.0015402,0.0015139,0.001488,0.0014626,0.0014376,0.0014131,0.001389,0.0013653,0.001342,0.001319,0.0012965,0.0012744,0.0012526,0.0012313,0.0012102,0.0011896,0.0011693,0.0011493,0.0011297,0.0011104,0.0010914,0.0010728,0.0010545,0.0010365,0.0010188,0.0010014,0.0009843,0.0009675,0.00095098,0.00093475,0.00091879,0.0009031,0.00088769,0.00087253,0.00085764,0.00084299,0.0008286,0.00081446,0.00080055,0.00078688,0.00077345,0.00076025,0.00074727,0.00073451,0.00072197,0.00070965,0.00069753,0.00068562,0.00067392,0.00066241,0.0006511,0.00063999,0.00062906,0.00061832,0.00060777,0.00059739,0.00058719,0.00057717,0.00056731,0.00055763,0.00054811,0.00053875,0.00052955,0.00052051,0.00051163,0.00050289,0.00049431,0.00048587,0.00047757,0.00046942,0.00046141,0.00045353,0.00044579,0.00043818,0.0004307,0.00042334,0.00041612,0.00040901,0.00040203,0.00039517,0.00038842,0.00038179,0.00037527,0.00036886,0.00036257,0.00035638,0.00035029,0.00034431,0.00033843,0.00033266,0.00032698,0.0003214,0.00031591,0.00031052,0.00030521,0.0003,0.00029488,0.00028985,0.0002849,0.00028004,0.00027526,0.00027056,0.00026594,0.0002614,0.00025693,0.00025255,0.00024824,0.000244};


#define MAX_MCC_LEN 4096*4
#define MAX_N_S 32

class MCC{
public:
// define some parameters
	int R;			// the radius of structure
	int N_S;		
	int N_D;
	float Delta_S;
	float Delta_D;


	float delta_S;
	float delta_D;

	float mu_Phi;
	float tau_Phi;


	int MCC_Len;
	float	F[MAX_MCC_LEN];
	char	B[MAX_MCC_LEN];

	MCC()
	{
		initialization(90, 10, 5);
	};
	MCC(int R, int NS, int ND)
	{
		initialization(R, NS, ND);
	};

	// initialization
	void initialization(int _R, int NS, int ND)
	{
		R = _R;
		N_S = NS;
		N_D = ND;

		Delta_S = (2.* R) / N_S;
		Delta_D = (2.* PI) / N_D;

		mu_Phi = 0.005;
		tau_Phi = 400;

		delta_S = 28./3.;
		delta_D = 2./9. * PI;
		MCC_Len = 0;

		memset(F, 0, sizeof(float)*MAX_MCC_LEN);
		memset(B, 0, sizeof(char)*MAX_MCC_LEN);
		memset(msk_cell, 0, sizeof(unsigned char) * MAX_N_S * MAX_N_S);

		get_msk_cell();
		get_layer_phi();
	};

	// the minutiae list within R+3*delta_S
	MinuList ML;
	
	vector<int> nei_minu_index[MAX_N_S * MAX_N_S];
	vector<float> nei_minu_dis_2[MAX_N_S * MAX_N_S];// the square of distance from minutiae to the cell

	vector<float> dphi;
	inline void get_layer_phi()
	{
		for(int k=1;k<=N_D;k++)
		{
			dphi.push_back(-PI + (k-0.5) * Delta_D);
		}
	};

	unsigned char msk_cell[MAX_N_S * MAX_N_S];


	// get the cell mask (remove the outer region of the circle)
	void get_msk_cell(){
        //compute vlaue for each cell in the base
        for(int j=1;j<=N_S;j++)
        {
            for(int i=1;i<=N_S;i++)
            {
                float x = (i-0.5) * Delta_S;
                float y = (j-0.5) * Delta_S;
                float d = (x-R) * (x-R) + (y-R) * (y-R);
                if (d<R*R)
                {
                    msk_cell[(j-1)*N_S+(i-1)] = 1;
                    MCC_Len++;
                    //printf("1 ");
                }//else{
                    //printf("0 ");
                //}
            }
            //printf("\r\n");
        }

        MCC_Len *= N_D;
    }
	
	// get neighborhood minutiae for all cell in the base
	void get_all_neighbor_minutiae()
    {
        //compute vlaue for each cell in the base
        for(int j=1;j<=N_S;j++)
        {
            for(int i=1;i<=N_S;i++)
            {
                if (!msk_cell[(j-1)*N_S+(i-1)]) continue;

                // the local coordinate w.r.t central minutiae
                float x = (i-0.5) * Delta_S - R;
                float y = (j-0.5) * Delta_S - R;

                nei_minu_index[(j-1)*N_S+(i-1)].clear();
                nei_minu_dis_2[(j-1)*N_S+(i-1)].clear();

                // search all minutiae for this cell
                for(int m=1;m<ML.size();m++)
                {
                    float d = ((x-ML.at(m).x) * (x-ML.at(m).x) + (y-ML.at(m).y) * (y-ML.at(m).y));
                    if (d<9*delta_S*delta_S)
                    {
                        nei_minu_index[(j-1)*N_S+(i-1)].push_back(m);
                        nei_minu_dis_2[(j-1)*N_S+(i-1)].push_back(d); // store the square distance
                    }
                }
                //printf("%d ", nei_minu_index[(j-1)*N_S+(i-1)].size());
            }
            //printf("\r\n");
        }
    }

	// compute the spatial contribution of one neighboring minutiae
	// m: the neighboring minutiae index number of the cell (i,j)
	// i: the cell index number (column)
	// j: the cell index number (row)
	inline float compute_C_m_S(int m, int i, int j)
    {
        // cell coordinates w.r.t. central minutiae
        //float x = (i-0.5) * Delta_S - R;
        //float y = (j-0.5) * Delta_S - R;

        //
        //float t = nei_minu_dis_2[(j-1)*N_S+(i-1)][m];
        //float val = exp(-nei_minu_dis_2[(j-1)*N_S+(i-1)][m] / (2.*delta_S*delta_S))
        //	/(delta_S*sqrt(2*PI));
        int h = nei_minu_dis_2[(j-1)*N_S+(i-1)][m] / 3;
        
        return G_S[h];
    }

	// compute the directional contribution of one neighboring minutiae
	// m the neighboring minutiae index number of the cell (i,j)
	float compute_C_m_D(int m, int i, int j, int k)
    {
        float dtheta = diffangle(ML.at(nei_minu_index[(j-1)*N_S+(i-1)][m]).theta,
            ML.at(0).theta);
        
        float alpha_k = diffangle(dphi[k-1], dtheta);

        // do the integral by lookup table
        int h = (alpha_k+PI) * 256 / (2 * PI);
        h = (h==256)?0:h;

        //if (h<0 || h>255)
        //	printf("Bad h = %d in compute_C_m_D() !\r\n", h);
        return (N_D==5)?G_D5[h]:G_D[h];
    }

	// compute the angle difference
	inline float diffangle(float theta1, float theta2)
	{
		if(theta1-theta2>=-PI && theta1-theta2<PI)
		{
			return theta1-theta2;
		}else if(theta1-theta2<-PI)
		{
			return 2*PI+theta1-theta2;
		}else{
			return -2*PI+theta1-theta2;
		}
	};

	inline float sigmf(float v)
	{
		float val = 1. / (1 + exp(-tau_Phi * (v-mu_Phi)));
		return val;
	}

	// MCC extraction
	void CreateMCC(float* realmcc, char* binmcc)
    {
        if (ML.size()==0) return;

        get_all_neighbor_minutiae();

        //compute vlaue for each
        int count = 0;
        for(int k=1;k<=N_D;k++)
        {
            for(int j=1;j<=N_S;j++)
            {
                for(int i=1;i<=N_S;i++)
                {
                    if (!msk_cell[(j-1)*N_S+(i-1)])
                    {
                        F[(k-1)*N_S*N_S + (j-1)*N_S + (i-1)] = 0.2;
                        B[(k-1)*N_S*N_S + (j-1)*N_S + (i-1)] = -1;
                        continue;
                    }

                    //printf("%d %d %d\r\n", i, j, k);

                    float s = 0.;
                    for(int m=0;m<nei_minu_index[(j-1)*N_S+(i-1)].size();m++)
                    {
                        float cms = compute_C_m_S(m, i, j);
                        float cmd = compute_C_m_D(m, i, j, k);
                        s += (cms * cmd);
                    }

                    float f = sigmf(s);
                    F[(k-1)*N_S*N_S + (j-1)*N_S + (i-1)] = f;
                    B[(k-1)*N_S*N_S + (j-1)*N_S + (i-1)] = (s>mu_Phi*0.7?1:0);

                    // output
                    if(realmcc!=NULL)
                    {
                        realmcc[count] = f;
                    }
                    if(binmcc!=NULL)
                    {
                        binmcc[count] = (s>mu_Phi?1:0);
                    }
                    count++;
                }
            }
        }

        
    }


	// Print MCC
	bool SaveMCC(const char* filename, char BF)
    {
        FILE* f = fopen(filename, "w");
        if(!f)
        {
            printf("Fail to open %s\r\n", filename);
            return false;
        }

        for(int k=N_D;k>=1;k--)
        {
            for(int j=1;j<=N_S;j++)
            {
                for(int i=1;i<=N_S;i++)
                {
                    switch(BF)
                    {
                    case 'F':
                        fprintf(f, "%f ", F[(k-1)*N_S*N_S + (j-1)*N_S + (i-1)]);
                        break;
                    case 'B':
                        fprintf(f, "%d ", (int)B[(k-1)*N_S*N_S + (j-1)*N_S + (i-1)]);
                        break;
                    case 'O':
                        if(msk_cell[(j-1)*N_S+(i-1)])
                        {
                            fprintf(f, "%f ", F[(k-1)*N_S*N_S + (j-1)*N_S + (i-1)]);
                        }
                        break;
                    }
                }
                if(BF!='O')	fprintf(f, "\n");
            }
        }

        fclose(f);
        return true;
    }

};

int GetMCCLen(float R, int NS, int ND);

// Extract MCC for one template
void ExtractMCC(MinuList& ML, int ND, int NS, int R, float *realmcc, char* binmcc,bool Rotation=true);

//
// the output M2 should in the order like mccsdk template
// thus, l = j*NS*ND+i*ND+k
// where j, i, k are the indices of y, x and theta
// DO NOT MISS LEAD BY THE PAMI PAPER
template<class T>
void MccFormat(T* M, int MccLen, int Num, unsigned char* Msk, int NS, int ND, T* M2)
{
    for(int n=0;n<Num;n++)
    {
        int h = 0;
        for(int k=0;k<ND;k++)
        {
            for(int j=0;j<NS;j++)
            {
                for(int i=0;i<NS;i++)
                {
                    if(Msk[j*NS+i]==0)continue;
                    int l=j*NS*ND+i*ND+k;
                    M2[n*NS*NS*ND+l] = M[n*MccLen+h];
                    h++;
                }
            }
        }
        assert(h==MccLen);
    }
}

template<class T>
bool SaveMcc(const char* filename, T* M, int MccLen, int Num, 
        unsigned char* CellMask, int NS, int ND, MinuList& ML,
        int imageWidth, int imageHeight, int Res)
{
    assert(Num==ML.size());

    T* M2 = new T[Num*NS*NS*ND];
    memset(M2,0,sizeof(T)*Num*NS*NS*ND);
    MccFormat(M, MccLen, Num, CellMask, NS, ND, M2);
    //for(int i=0;i<NS*NS*ND;i++)
    //    cout << M2[i]<<" ";

    ofstream ofile(filename);
    if(!ofile.is_open())
    {
        return false;
    }

    ofile<<imageWidth<<"\r\n";
    ofile<<imageHeight<<"\r\n";
    ofile<<Res<<"\r\n";
    ofile<<ML.size()<<"\r\n";
    // save minutiae
    for(int i=0;i<ML.size();i++)
    {
        ofile<<ML[i].x<<" "<<ML[i].y<<" "<<ML[i].theta<<"\r\n";
    }

    // save mcc
    ofile<<Num<<"\r\n";
    for(int n=0;n<Num;n++)
    {
        ofile<<"True ";
        for(int j=0;j<NS;j++)
        {
            for(int i=0;i<NS;i++)
            {
                if(CellMask[j*NS+i]==0)
                {
                    ofile<<0<<" ";
                }
                else
                {
                    ofile<<1<<" ";
                }
            }
        }

        int tmp = 0;
        for(int j=0;j<NS;j++)
        {
            for(int i=0;i<NS;i++)
            {
                for(int k=0;k<ND;k++)
                {
                    int l = i*NS*ND+j*ND+k;
                    string str = (k==ND-1&&j==NS-1&&i==NS-1)?"\r\n":" ";
                    if(CellMask[j*NS+i]==0)
                    {
                        ofile<<0<<str;
                        assert(M2[n*NS*NS*ND+l]==0);
                    }
                    else
                    {
                        tmp++;
                        if(sizeof(T)==sizeof(char))
                        {
                            ofile<<int(M2[n*NS*NS*ND+l])<<str;
                        }
                        else
                        {
                            ofile<<M2[n*NS*NS*ND+l]<<str;
                        }
                    }
                }
            }
        }
        assert(tmp==MccLen);
    }
    
    delete[] M2;
    return true;
}

template<class T>
vector< vector<uint8_t> > SaveMccToVector(T* M, int MccLen, int Num, 
        unsigned char* CellMask, int NS, int ND, MinuList& ML)
{
    assert(Num==ML.size());

    T* M2 = new T[Num*NS*NS*ND];
    memset(M2,0,sizeof(T)*Num*NS*NS*ND);
    MccFormat(M, MccLen, Num, CellMask, NS, ND, M2);

    vector< vector<uint8_t> > retorno(Num); 

    for(int n=0;n<Num;n++)
    {
        for(int j=0;j<NS;j++)
        {
            for(int i=0;i<NS;i++)
            {
                if(CellMask[j*NS+i]==0)
                {
                    retorno[n].push_back(0);
                }
                else
                {
                    retorno[n].push_back(1);
                }
            }
        }

        int tmp = 0;
        for(int j=0;j<NS;j++)
        {
            for(int i=0;i<NS;i++)
            {
                for(int k=0;k<ND;k++)
                {
                    int l = i*NS*ND+j*ND+k;
                    if(CellMask[j*NS+i]==0)
                    {
                        retorno[n].push_back(0);
                        assert(M2[n*NS*NS*ND+l]==0);
                    }
                    else
                    {
                        tmp++;
                        if(sizeof(T)==sizeof(char))
                        {
                            retorno[n].push_back(int(M2[n*NS*NS*ND+l]));
                        }
                        else
                        {
                            retorno[n].push_back(M2[n*NS*NS*ND+l]);
                        }
                    }
                }
            }
        }
        assert(tmp==MccLen);
    }
    
    delete[] M2;
    return retorno;
}
#endif
