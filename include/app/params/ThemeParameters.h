#ifndef _APP_PARAMS_THEMEPARAMETERS_H_
#define _APP_PARAMS_THEMEPARAMETERS_H_

//STL
#include <string>

//EPG
#include <epg/params/ParametersT.h>
#include <epg/SingletonT.h>



	enum THEME_PARAMETERS{
		DB_CONF_FILE,

		WORKING_SCHEMA,
		REF_SCHEMA,
		EDGE_TABLE_INIT,
		TABLE_REF_NAME,

		COUNTRY_CODE_W,
		NAT_ID_NAME,

		//LIST_ATTR_JSON,
		LIST_ATTR_W

	};

namespace app{
namespace params{

	class ThemeParameters : public epg::params::ParametersT< THEME_PARAMETERS >
	{
		typedef  epg::params::ParametersT< THEME_PARAMETERS > Base;

		public:

			/// \brief
			ThemeParameters();

			/// \brief
			~ThemeParameters();

			/// \brief
			virtual std::string getClassName()const;

	};

	typedef epg::Singleton< ThemeParameters >   ThemeParametersS;

}
}

#endif