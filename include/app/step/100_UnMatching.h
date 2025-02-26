#ifndef _APP_STEP_UNMATCHING_H_
#define _APP_STEP_UNMATCHING_H_

#include <epg/step/StepBase.h>
#include <app/params/ThemeParameters.h>

namespace app{
namespace step{

	class UnMatching : public epg::step::StepBase< app::params::ThemeParametersS > {

	public:

		/// \brief
		int getCode() { return 100; };

		/// \brief
		std::string getName() { return "UnMatching"; };

		/// \brief
		void onCompute( bool );

		/// \brief
		void init();

	};

}
}

#endif