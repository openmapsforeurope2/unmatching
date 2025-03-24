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
			std::string const edgeTableName = context->getEpgParameters().getValue(EDGE_TABLE).toString();
			
			// app parameters
			params::ThemeParameters *themeParameters = params::ThemeParametersS::getInstance();
			std::string refTableName = themeParameters->getValue(TABLE_REF_NAME).toString();
			std::string listAttrWName = themeParameters->getValue(LIST_ATTR_W).toString();
			//std::string listAttrJsonName = themeParameters->getValue(LIST_ATTR_JSON).toString();
			_setListToSetAttr(listAttrWName, _sAttrNameW, "/");
			//_setListToSetAttr(listAttrJsonName, _sAttrNameJson, "/");

			//--
			_fsEdgeW = context->getDataBaseManager().getFeatureStore(edgeTableName, idName, geomName);
			_fsRef= context->getDataBaseManager().getFeatureStore(refTableName, idName, geomName);

			//--

			//--
			_logger->log(epg::log::INFO, "[END] initialization: " + epg::tools::TimeTools::getTime());
		};

		///
		///
		///
		void UnMatchingOp::_compute()  {
			//--
			epg::Context *context = epg::ContextS::getInstance();

			// epg parameters
			epg::params::EpgParameters const& epgParams = context->getEpgParameters();
			std::string const geomName = epgParams.getValue(GEOM).toString();
			std::string const countryCodeName = epgParams.getValue(COUNTRY_CODE).toString();

			// app parameters
			params::ThemeParameters *themeParameters = params::ThemeParametersS::getInstance();
			std::string natIdName = themeParameters->getValue(NAT_ID_NAME).toString();

			std::set<std::string> idEdg2delete;

			ign::feature::FeatureType featTypEdgW = _fsEdgeW->getFeatureType();
			std::vector<std::string> vAttrNames;
			featTypEdgW.getAttributeNames(vAttrNames);

			boost::progress_display display(_fsEdgeW->numFeatures(), std::cout, "[ UNMATCHING ]\n");

			ign::feature::FeatureIteratorPtr itEdgeW= _fsEdgeW->getFeatures(ign::feature::FeatureFilter());
			while (itEdgeW->hasNext()) {
				ign::feature::Feature fEdgW = itEdgeW->next();
				++display;
				std::string countryCodeEdgW = fEdgW.getAttribute(countryCodeName).toString();
				if (countryCodeEdgW.find("#") == std::string::npos) {
					idEdg2delete.insert(fEdgW.getId());
					continue;
				}

				size_t nposCountry = _getPosCountryCode(countryCodeEdgW);

				std::string natIdEdgW = fEdgW.getAttribute(natIdName).toString();

				std::vector<std::string> vNatIdEdgW;
				epg::tools::StringTools::Split(natIdEdgW, "#", vNatIdEdgW);
				std::string natIdEdgAttrRef = vNatIdEdgW[vNatIdEdgW.size() - 1 - nposCountry];

				ign::feature::FeatureIteratorPtr itRef = _fsRef->getFeatures(ign::feature::FeatureFilter(natIdName + "='"+ natIdEdgAttrRef+"'"));

				if (!itRef->hasNext()) {
					//pas de ref donc unmatch autrement?
					_logger->log(epg::log::WARN, "pas d'objet trouve dans Ref avec le "+ natIdEdgW +" : " + natIdEdgAttrRef);
					continue;
				}
				
				//si plusieurs obj?
				ign::feature::Feature fRef = itRef->next();

				for (size_t i = 0; i < vAttrNames.size(); ++i) {
					std::string attrName = vAttrNames[i];
					if (_sAttrNameW.find(attrName) != _sAttrNameW.end()) 
						continue;
					fEdgW.setAttribute(attrName, fRef.getAttribute(attrName));
				}

				/*
				for (size_t i = 0; i < vAttrNames.size(); ++i) {
					std::string attrUnmatchedValue;
					std::string attrName = vAttrNames[i];

					if (_sAttrNameW.find(attrName) != _sAttrNameW.end()) 
						continue;

					if (_sAttrNameJson.find(attrName) != _sAttrNameJson.end()) {
						//suppr de la npos valeur si plusieurs ?
						continue;
					}

					std::string attr2unMatched = fEdgW.getAttribute(attrName).toString();

					std::vector<std::string> vAttrib2unmatch;
					epg::tools::StringTools::Split(attr2unMatched, "#", vAttrib2unmatch);

					if (vAttrib2unmatch.size() < 2)
						continue;
					else
						fEdgW.setAttribute(attrName,ign::data::String(vAttrib2unmatch[nposCountry]));

				}*/

				_fsEdgeW->modifyFeature(fEdgW);
			}	

			boost::progress_display display2(idEdg2delete.size(), std::cout, "[ DELETE COUNTRY BEFORE UP ]\n");
			for (std::set<std::string>::const_iterator sit = idEdg2delete.begin(); sit != idEdg2delete.end(); ++sit) {
				++display2;
				_fsEdgeW->deleteFeature(*sit);
			}

		}


		///
		///
		///

		void UnMatchingOp::_setListToSetAttr(
			std::string& listAttrName,
			std::set<std::string>& setAttrName,
			std::string separator
		) {
			std::vector<std::string> vAttrName;
			epg::tools::StringTools::Split(listAttrName, separator, vAttrName);
			for (size_t i = 0; i < vAttrName.size(); ++i) {
				setAttrName.insert(vAttrName[i]);
			}
		}


		///
	///
	///
		size_t UnMatchingOp::_getPosCountryCode(std::string countryCodeDouble) {
			std::vector<std::string> vCountryCodeByParts;
			epg::tools::StringTools::Split(countryCodeDouble, "#", vCountryCodeByParts);
			if (vCountryCodeByParts[0] == _countryCode)
				return 0;
			return 1;
		}

		

	}
}