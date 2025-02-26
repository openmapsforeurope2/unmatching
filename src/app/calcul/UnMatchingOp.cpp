// APP
#include <app/calcul/UnMatchingOp.h>
#include <app/params/ThemeParameters.h>

// BOOST
#include <boost/progress.hpp>

// EPG
#include <epg/Context.h>
#include <epg/params/EpgParameters.h>
#include <epg/sql/tools/numFeatures.h>
#include <epg/sql/DataBaseManager.h>
#include <epg/tools/StringTools.h>
#include <epg/tools/TimeTools.h>
#include <epg/tools/FilterTools.h>
// #include <epg/tools/geometry/simplifyLineString.h>
#include <epg/tools/geometry/getArea.h>
#include <epg/tools/geometry/ToValidGeometry.h>

// IGN
#include <ign/geometry/algorithm/SimplifyOpGeos.h>


namespace app
{
	namespace calcul
	{
		///
		///
		///
		UnMatchingOp::UnMatchingOp(
			std::string countryCode,
			bool verbose
		) :
			_countryCode(countryCode),
			_verbose(verbose)
		{
			_init();
		}

		///
		///
		///
		UnMatchingOp::~UnMatchingOp()
		{

			// _shapeLogger->closeShape("ps_cutting_ls");
		}

		///
		///
		///
		void UnMatchingOp::Compute(
			std::string countryCode,
			bool verbose
		) {
			UnMatchingOp op(countryCode, verbose);
			op._compute();
		}

		///
		///
		///
		void UnMatchingOp::_init()
		{
			//--
			_logger = epg::log::EpgLoggerS::getInstance();
			_logger->log(epg::log::INFO, "[START] initialization: " + epg::tools::TimeTools::getTime());

			//--
			_shapeLogger = epg::log::ShapeLoggerS::getInstance();
			// _shapeLogger->addShape("ps_cutting_ls", epg::log::ShapeLogger::POLYGON);

			//--
			epg::Context *context = epg::ContextS::getInstance();

			// epg parameters
			epg::params::EpgParameters const& epgParams = context->getEpgParameters();
			std::string const idName = epgParams.getValue(ID).toString();
			std::string const geomName = epgParams.getValue(GEOM).toString();
			std::string const countryCodeName = epgParams.getValue(COUNTRY_CODE).toString();
			std::string const borderTableName = epgParams.getValue(TARGET_BOUNDARY_TABLE).toString();

			// app parameters
			params::ThemeParameters *themeParameters = params::ThemeParametersS::getInstance();
			std::string const themeName = themeParameters->getValue(THEME_W).toString();
			std::string const tableName = themeParameters->getValue(TABLE_W).toString();
			std::string refTableName = tableName + themeParameters->getValue(TABLE_REF_SUFFIX).toString();
			std::string upTableName = tableName + themeParameters->getValue(TABLE_UP_SUFFIX).toString();
			std::string cdTableName = tableName + themeParameters->getValue(TABLE_CD_SUFFIX).toString();
			std::string upAreaTableName = tableName + themeParameters->getValue(TABLE_UP_AREA_SUFFIX).toString();


			//--
			// _fsProd = context->getDataBaseManager().getFeatureStore(tableName, idName, geomName);
			_fsRef = context->getDataBaseManager().getFeatureStore(refTableName, idName, geomName);
			_fsUp = context->getDataBaseManager().getFeatureStore(upTableName, idName, geomName);
			_fsCd = context->getDataBaseManager().getFeatureStore(cdTableName, idName, geomName);
			_fsBorder = context->getDataBaseManager().getFeatureStore(borderTableName, idName, geomName);
			_fsUpArea = context->getDataBaseManager().getFeatureStore(upAreaTableName, idName, geomName);

			//--
			_logger->log(epg::log::INFO, "[END] initialization: " + epg::tools::TimeTools::getTime());
		};

		///
		///
		///
		void UnMatchingOp::_compute() const {
			//--
			epg::Context *context = epg::ContextS::getInstance();

			// epg parameters
			epg::params::EpgParameters const& epgParams = context->getEpgParameters();
			std::string const geomName = epgParams.getValue(GEOM).toString();
			std::string const countryCodeName = epgParams.getValue(COUNTRY_CODE).toString();
			std::string const boundaryTypeName = epgParams.getValue(BOUNDARY_TYPE).toString();
			std::string const interBoundaryTypeValue = epgParams.getValue(TYPE_INTERNATIONAL_BOUNDARY).toString();

			// app parameters
			params::ThemeParameters *themeParameters = params::ThemeParametersS::getInstance();
			std::string const idRefName = themeParameters->getValue(ID_REF).toString();
			std::string const idUpName = themeParameters->getValue(ID_UP).toString();
			std::string const distThreshold = themeParameters->getValue(UA_DIST_THRESHOLD).toString();




		}


	}
}
