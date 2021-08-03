#ifndef _WDS_COMMON_H
#define _WDS_COMMON_H

/*************************************************************************************
 * Defines....
 *************************************************************************************/

#define QC_NO_MWS				-1

/* QC  */
#define QC_TYPE_PRE				'P'
#define QC_TYPE_TMP				'T'
#define QC_TYPE_REH				'R'
#define QC_TYPE_PTY				'Y'
#define QC_TYPE_PM25			'2'
#define QC_TYPE_W				'W'
#define QC_TYPE_NOW				'N'

/* QC  */
#define QC_LIMIT_DISTANCE		1.0
#define QC_LIMIT_HOUR			6
#define QC_SURROUND_DISTANCE	2.0
#define QC_SURROUND_HOUR		1
#define QC_MIN_DATA_COUNT		100

/* QC */
#define QC_GRIB					"/usr/local/kwgrib2/kwgrib2"
#define QC_MODEL_DIR			"/home/kmiti/model"
#define QC_MODEL_CACHE_DIR		"/home/~/model_cache"
#define QC_MODEL_GRID_DISTANCE	25
#define QC_MODEL_GRID_COUNT		2
#define QC_MODEL_GRID_SIZE		QC_MODEL_GRID_COUNT*2+1

/* QC */
#define QC_ERROR_OK				1
#define QC_ERROR_RANGE			-11
#define QC_ERROR_LIMIT			-12
#define QC_ERROR_MODEL			-13
#define QC_ERROR_EXT			-14
#define QC_ERROR_REVISE			-15
#define QC_ERROR_SELF_LIMIT		-16
#define QC_ERROR_INTER_RELATION	-17
#define QC_ERROR_RAIN			-18
#define QC_ERROR_SURROUND		-19
#define QC_ERROR_SPEC			-98
#define QC_ERROR_COMMON			-99

/* QC  */
#define QC_PRE_MAX				(double)1100
#define QC_PRE_MIN				(double)900
#define QC_TMP_MAX				(double)50
#define QC_TMP_MIN				(double)-50
#define QC_REH_MAX				(double)100
#define QC_REH_MIN				(double)10
#define QC_PM25_MAX				(double)300
#define QC_PM25_MIN				(double)0.01

 
#define NX		149		/* X */
#define NY		253		/* Y */

struct lamc_parameter
{
	float	Re;          /* [ km ]      */
	float	grid;        /* [ km ]      */
	float	slat1;       /* [degree]    */
	float	slat2;       /* [degree]    */
	float	olon;        /* [degree]    */
	float	olat;        /* [degree]    */
	float	xo;          /*  X          */
	float	yo;          /*  Y          */
	int		first;       /*             */
};


struct mws_data
{
	long	serial_no;
	int		fcount;
	double*	fdata;
};

/*************************************************************************************
 * Global 
 *************************************************************************************/

char	QC_errmsg[256];

/*************************************************************************************
 * 
 *************************************************************************************/

int  	QualityCheck(char type, double value, double lng, double lat, int kdate, int ktime, long mws_serial, sql_context ctx);
int  	QC_ClimateCheck(char type, double value, double lng, double lat);
int  	QC_SelfLimitCheck(char type, double value, double lng, double lat, time_t timep, long mws_serial, sql_context ctx);
//int  	QC_RangeLimitCheck(char type, double value, double lng, double lat, time_t timep, sql_context ctx);
int		QC_GetSurroundPoint(double lng, double lat, time_t timep, sql_context ctx);
int  	QC_RangeLimitCheck1(char type, double value, double lng, double lat, time_t timep, sql_context ctx);
int  	QC_RangeLimitCheck2(char type, double value, double lng, double lat, time_t timep, sql_context ctx);
int  	QC_RainCheck(char type, double value, double lng, double lat, time_t timep, sql_context ctx);
int		QC_ModelCheck(char type, double value, double lng, double lat, time_t timep);
int		QC_AirKoreaCheck(char type, double value, double lng, double lat, time_t timep, long mws_serial, sql_context ctx);

double	haversine_km(double lng1, double lat1, double lng2, double lat2);
void	latitude_range(double lat, double dkm, double* minlat, double* maxlat);
void	longitude_range(double lng, double lat, double dkm, double* minlng, double* maxlng);
double	earth_radius(double lat);

int  	ConvertXYLonLat(int mode, float var1, float var2, float* ret1, float* ret2);
int  	map_conv(float* lon, float* lat, float* x, float* y, int code, struct lamc_parameter map);
int  	lamcproj(float* lon, float* lat, float* x, float* y, int code, struct lamc_parameter* map);

#endif
