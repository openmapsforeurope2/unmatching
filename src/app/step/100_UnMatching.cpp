#include <app/step/100_UnMatching.h>

//EPG
#include <epg/Context.h>
#include <epg/log/ScopeLogger.h>

//APP
#include <app/params/ThemeParameters.h>
#include <app/calcul/UnMatchingOp.h>


namespace app {
namespace step {

	///
	///
	///
	void UnMatching::init()
	{
		// addWorkingEntity(AREA_TABLE_INIT);
	}

	///
	///
	///
	void UnMatching::onCompute( bool verbose = false )
	{
		app::params::ThemeParameters* themeParameters = app::params::ThemeParametersS::getInstance();
		std::string countryCodeW = themeParameters->getParameter(COUNTRY_CODE_W).getValue().toString();

		app::calcul::UnMatchingOp::Compute(countryCodeW, verbose);
	}

}
}
