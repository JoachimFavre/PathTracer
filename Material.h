#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "Ray.h"

/*!
    \file Material.h
    \brief Defines the Material class and the functions around it.

    \class Material
    \brief Abstrat class that models a material.

    \fn Material::Material(DoubleVec3D emittance = 0)
    \brief Default and main constructor.
    \param emittance The light this material emits.

    \fn Material::Material(const Material& material)
    \brief Copy constructor.
    \param material The material that will be copied.

    \fn DoubleVec3D Material::getEmittance()
    \brief Getter for the emittance attribute.
    \return The emittance of this material.

    \fn void Material::setEmittance(DoubleVec3D emittance)
    \brief Setter for the emittance attribute.
    \param emittance The new emittance of this material.

    \fn virtual Material* Material::deepCopy() = 0
    \brief Makes a deep copy of this material.
    \return A pointer to a deeply copied version of this material.

    \fn virtual DoubleUnitVec3D Material::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal) = 0
    \brief Computes the new ray direction.
    \param previousRay The ray that hits this material.
    \param normal The normal at the intersection.

    \fn virtual DoubleVec3D Material::computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double angleNewDirectionNormal, bool nextEventEstimation = false) = 0
    \brief Computes the new radiance.
    \param recursiveRadiance The radiance recursively obtained.
    \param angleNewDirectionNormal The cosine of the angle between the direction of the next ray and the normal at the intersection.
    \param nextEventEstimation Whether the radiance is obtained using the next event estimation algorithm.
    \return The new radiance.

    \fn virtual bool Material::worksWithNextEventEstimation() = 0
    \brief Returns whether this material works with next event estimation.
    \return True if this material works with the next event estimation algorithm, false else.

    \fn virtual std::ostream& Material::getDescription(std::ostream& stream) = 0
    \brief Returns this material's description.
    \param stream The current stream.
    \return The stream with the description.

    \fn virtual std::string Material::getType() = 0
    \brief Returns this material type.
    \return Returns this material type ("Diffuse", "Refractive", ...)

    \fn virtual json Material::getSpecificParametersJson() = 0
    \brief Converts this material's specific parameters to json.
    \return This material's specific parameters converted to json.

    \fn virtual void Material::setSpecificParametersJson(const json& j) = 0
    \brief Sets this material's specific parameters according to json.
    \param j The json input.

    \fn std::ostream& operator<<(std::ostream& stream, const Material& material)
    \brief Ostream operator.
    \details Calls the getDescription() method.
    \param stream The ostream before.
    \param material The material that will be added to the stream.
    \return The stream with the material added.
    \sa getDescription()
*/

class Material {
private:
    DoubleVec3D emittance;

public:
    Material(DoubleVec3D emittance = 0);
    Material(const Material& material);

    DoubleVec3D getEmittance() const;
    void setEmittance(DoubleVec3D emittance);

    virtual Material* deepCopy() const = 0;
    
    virtual DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal) const = 0;
    virtual DoubleVec3D computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double angleNewDirectionNormal, bool nextEventEstimation = false) const = 0;
    virtual bool worksWithNextEventEstimation() const = 0;

    virtual std::ostream& getDescription(std::ostream& stream) const = 0;
    virtual std::string getType() const = 0;
    virtual json getSpecificParametersJson() const = 0;
    virtual void setSpecificParametersJson(const json& j) = 0;
};

std::ostream& operator<<(std::ostream& stream, const Material& material);

#endif
