
//APP
#include <app/params/ThemeParameters.h>

//SOCLE
#include <ign/Exception.h>


namespace app{
namespace params{


	///
	///
	///
	ThemeParameters::ThemeParameters()
	{
		_initParameter( DB_CONF_FILE, "DB_CONF_FILE");
		_initParameter(WORKING_SCHEMA, "WORKING_SCHEMA");
		_initParameter(REF_SCHEMA, "REF_SCHEMA");
		_initParameter(EDGE_TABLE_INIT, "EDGE_TABLE_INIT"); 
		_initParameter(TABLE_REF_NAME, "TABLE_REF_NAME");
		_initParameter(COUNTRY_CODE_W, "COUNTRY_CODE_W");
		_initParameter(NAT_ID_NAME, "NAT_ID_NAME");
		//_initParameter(LIST_ATTR_JSON, "LIST_ATTR_JSON");
		_initParameter(LIST_ATTR_W, "LIST_ATTR_W");
		
	}

	///
	///
	///
	ThemeParameters::~ThemeParameters()
	{
	}

	///
	///
	///
	std::string ThemeParameters::getClassName()const
	{
		return "app::params::ThemeParameters";
	}


}
}