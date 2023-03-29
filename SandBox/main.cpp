#include <memory>
#include <iostream>


class Collar
{
public:
	enum class TYPE
	{
		PLASTIC,
		LEATHER
	};
	Collar(const TYPE& type_, const std::string colorName_) :
		colorName(colorName_), type(type_)
	{
	}
	//Data
	std::string colorName;
	TYPE type;
};

class SmartDog
{
public:
	SmartDog(std::unique_ptr<Collar> puCollar_, const std::string& dogName_) :
		puCollar(std::move(puCollar_)), dogName(dogName_)
	{

	}


	SmartDog(const SmartDog& smartDog)
	{
		this->puCollar = std::make_unique<Collar>(smartDog.puCollar->type, smartDog.puCollar->colorName);
		this->dogName = smartDog.dogName;
	}

	SmartDog& operator=(const SmartDog& smartDog)
	{
		if (this != &smartDog)
		{

			try
			{
				std::unique_ptr<Collar>  pTempCollar = std::make_unique<Collar>(smartDog.puCollar->type, smartDog.puCollar->colorName);
				this->puCollar = std::move(pTempCollar);
				this->dogName = smartDog.dogName;
			}
			catch (const std::bad_alloc& st)
			{
				std::cout << "Memory allocation issue :" << st.what() << '\n';
				return *this;
			}

		}
		return *this;
	}



	~SmartDog() = default;

	std::unique_ptr<Collar> puCollar; //There is an aggregation relationship between Dog and Collar
	std::string dogName;
};


int main()
{

	std::unique_ptr<Collar> puCollarPink = std::make_unique<Collar>(Collar::TYPE::LEATHER, "Pink");
	std::unique_ptr<Collar> puCollarBlue = std::make_unique<Collar>(Collar::TYPE::PLASTIC, "Blue");
	std::unique_ptr<Collar> puCollarYellow = std::make_unique<Collar>(Collar::TYPE::PLASTIC, "Yellow");

	SmartDog coco(std::move(puCollarPink), "Coco");
	SmartDog miko(std::move(puCollarBlue), "Miko");


	SmartDog zizi(coco);

	{
		SmartDog yummy(std::move(puCollarYellow), "Yummy");
		yummy = miko;
	}
	miko = zizi;
	std::cout << miko.dogName << '\n';
	miko = miko;
	std::cout << miko.dogName << '\n';




	return 0;
}

