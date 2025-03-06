#ifndef _APP_CALCUL_UNMATCHINGOP_H_
#define _APP_CALCUL_UNMATCHINGOP_H_


//SOCLE
#include <ign/feature/sql/FeatureStorePostgis.h>

//EPG
#include <epg/log/EpgLogger.h>
#include <epg/log/ShapeLogger.h>


namespace app{
namespace calcul{

	class UnMatchingOp {

	public:

	
        /// @brief 
        /// @param countryCode 
        /// @param verbose 
		UnMatchingOp(
            std::string countryCode,
            bool verbose
        );

        /// @brief 
        ~UnMatchingOp();


		/// \brief
		static void Compute(
			std::string countryCode, 
			bool verbose
		);


	private:
		//--
		ign::feature::sql::FeatureStorePostgis*                  _fsEdgeW;
		ign::feature::sql::FeatureStorePostgis*                  _fsRef;
		//--
		epg::log::EpgLogger*                                     _logger;
		//--
		epg::log::ShapeLogger*                                   _shapeLogger;
		//--
		std::string                                              _countryCode;
		//--
		bool                                                     _verbose;

		//--
		std::set<std::string>									_sAttrNameW;


	private:

		//--
		void _init();

		//--
		void _compute() ;


		//--
		void _setListToSetAttr(
			std::string& listAttrName,
			std::set<std::string>& setAttrName,
			std::string separator
		);

		//--
		size_t _getPosCountryCode(std::string countryCodeDouble);
    };

}
}

#endif