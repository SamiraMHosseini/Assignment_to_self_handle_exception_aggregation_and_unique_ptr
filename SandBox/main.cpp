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
	SmartDog(std::unique_ptr<Collar> pCollar_, const std::string& dogName_) :
		pCollar(std::move(pCollar_)), dogName(dogName_)
	{

	}


	SmartDog(const SmartDog& smartDog)
	{
		this->pCollar = std::make_unique<Collar>(smartDog.pCollar->type, smartDog.pCollar->colorName);
		this->dogName = smartDog.dogName;
	}

	SmartDog& operator=(const SmartDog& smartDog)
	{
		if (this != &smartDog)
		{

			try
			{
				std::unique_ptr<Collar>  pTempCollar = std::make_unique<Collar>(smartDog.pCollar->type, smartDog.pCollar->colorName);
				this->pCollar = std::move(pTempCollar);
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
	//There is an aggregation relationship between Dog and Collar 
	//The pointer is not owned by the class Dog
	/*
	This sentence means that the Dog class has a Collar class as one of its properties or attributes. 
	In other words, a Dog can have a Collar, but the Collar does not depend on the existence of the Dog.
	*/
	std::unique_ptr<Collar> pCollar; 
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

