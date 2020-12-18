#ifndef DEF_REFRACTIVEMATERIAL
#define DEF_REFRACTIVEMATERIAL

#include "Material.h"

/*!
    \file RefractiveMaterial.h
    \brief Defines the RefractiveMaterial class.

    \class RefractiveMaterial
    \brief Models a refractive material.

    \fn RefractiveMaterial::RefractiveMaterial(double refractiveIndex = 1.5, DoubleVec3D emittance = 0)
    \brief Default and main constructor.
    \param refractiveIndex The refractive index of this material.
    \param emittance The light this material emits.

    \fn RefractiveMaterial::RefractiveMaterial(const RefractiveMaterial& material)
    \brief Copy constructor.
    \param material The material that will be copied.

    \fn RefractiveMaterial::getRefractiveIndex()
    \brief Getter for the refractiveIndex attribute.
    \return The refractive index of this material.
    \sa setRefractiveIndex()

    \fn RefractiveMaterial::setRefractiveIndex(double refractiveIndex)
    \brief Setter for the refractiveIndex attribute.
    \param refractiveIndex The new refractive index of this material.
    \sa getRefractiveIndex()

    \fn RefractiveMaterial::deepCopy()
    \brief Makes a deep copy of this material.
    \return A pointer to a deeply copied version of this material.

    \fn RefractiveMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal)
    \brief Computes the new ray direction.
    \param previousRay The ray that hits this material.
    \param normal The normal at the intersection.

    \fn RefractiveMaterial::computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double angleNewDirectionNormal, bool nextEventEstimation = false)
    \brief Computes the new radiance.
    \param recursiveRadiance The radiance recursively obtained.
    \param angleNewDirectionNormal The cosine of the angle between the direction of the next ray and the normal at the intersection.
    \param nextEventEstimation Whether the radiance is obtained using the next event estimation algorithm.
    \return The new radiance.

    \fn RefractiveMaterial::worksWithNextEventEstimation()
    \brief Returns whether this material works with next event estimation.
    \return False.

    \fn RefractiveMaterial::getDescription(std::ostream& stream)
    \brief Returns this material's description.
    \param stream The current stream.
    \return The stream with the description.

    \fn RefractiveMaterial::getType()
    \brief Returns "Refractive"

    \fn RefractiveMaterial::getSpecificParametersJson()
    \brief Converts this material's specific parameters to json.
    \return This material's specific parameters converted to json.

    \fn RefractiveMaterial::setSpecificParametersJson(const json& j)
    \brief Sets this material's specific parameters according to json.
    \param j The json input.
*/

class RefractiveMaterial : public Material {
private:
    double refractiveIndex;

public:
    RefractiveMaterial(double refractiveIndex = 1.5, DoubleVec3D emittance = 0);
    RefractiveMaterial(const RefractiveMaterial& material);

    double getRefractiveIndex() const;
    void setRefractiveIndex(double refractiveIndex);
    
    Material* deepCopy() const;

    DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal) const;
    DoubleVec3D computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double angleNewDirectionNormal, bool nextEventEstimation = false) const;
    bool worksWithNextEventEstimation() const;

    std::ostream& getDescription(std::ostream& stream) const;
    std::string getType() const;
    json getSpecificParametersJson() const;
    void setSpecificParametersJson(const json& j);
};

#endif
