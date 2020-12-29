#ifndef DEF_SPECULARMATERIAL
#define DEF_SPECULARMATERIAL

#include "Material.h"

/*!
    \file SpecularMaterial.h
    \brief Defines the SpecularMaterial class.

    \class SpecularMaterial
    \brief Models a specular material

    \fn SpecularMaterial::SpecularMaterial(DoubleVec3D emittance = 0)
    \brief Default and main constructor.
    \param emittance The light this material emits.

    \fn SpecularMaterial::SpecularMaterial(const SpecularMaterial& material)
    \brief Copy constructor.
    \param material The material that will be copied.

    \fn Material* SpecularMaterial::deepCopy()
    \brief Makes a deep copy of this material.
    \return A pointer to a deeply copied version of this material.

    \fn DoubleUnitVec3D SpecularMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal)
    \brief Computes the new ray direction.
    \param previousRay The ray that hits this material.
    \param normal The normal at the intersection.

    \fn DoubleVec3D SpecularMaterial::computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double angleNewDirectionNormal, bool nextEventEstimation = false)
    \brief Computes the new radiance.
    \param recursiveRadiance The radiance recursively obtained.
    \param angleNewDirectionNormal The cosine of the angle between the direction of the next ray and the normal at the intersection.
    \param nextEventEstimation Whether the radiance is obtained using the next event estimation algorithm.
    \return The new radiance.

    \fn bool SpecularMaterial::worksWithNextEventEstimation()
    \brief Returns whether this material works with next event estimation.
    \return False.

    \fn std::ostream& SpecularMaterial::getDescription(std::ostream& stream)
    \brief Returns this material's description.
    \param stream The current stream.
    \return The stream with the description.

    \fn std::string SpecularMaterial::getType()
    \brief Returns "Specular".

    \fn json SpecularMaterial::getSpecificParametersJson()
    \brief Converts this material's specific parameters to json.
    \return This material's specific parameters converted to json.

    \fn void SpecularMaterial::setSpecificParametersJson(const json& j)
    \brief Sets this material's specific parameters according to json.
    \param j The json input.
*/

class SpecularMaterial : public Material {
public:
    SpecularMaterial(DoubleVec3D emittance = 0);
    SpecularMaterial(const SpecularMaterial& material);

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