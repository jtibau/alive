#pragma once



namespace alice{
	namespace poly{
		namespace utils{

			gmtl::Matrix44f convertMatrix(osg::Matrix original){
				original.invert(original);
				gmtl::Matrix44f converted;
				converted.set(original(0,0),original(1,0),original(2,0),original(3,0),
					original(0,1),original(1,1),original(2,1),original(3,1),
					original(0,2),original(1,2),original(2,2),original(3,2),
					original(0,3),original(1,3),original(2,3),original(3,3));
				return converted;
			}

			osg::Matrix convertMatrix(gmtl::Matrix44f original){
				osg::Matrix converted(original.getData());
				converted.invert(converted);
				return converted;
			}

			float* loadHomographyFromFile(std::string file){
				float* homography = new float[16];

				std::string line;
				std::ifstream data(file.c_str());

				for(int i=0; i<16; i++){
					std::getline(data,line,':');
					std::istringstream iss(line);
					iss >> std::dec >> homography[i];
				}
				return homography;
			}

		}
	}
}
