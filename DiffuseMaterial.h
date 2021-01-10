#ifndef DEF_DIFFUSEMATERIAL
#define DEF_DIFFUSEMATERIAL

#include "Material.h"

/*!
    \file DiffuseMaterial.h
    \brief Defines the DiffuseMaterial class.

    \class DiffuseMaterial
    \brief Models a diffuse material.

    \fn DiffuseMaterial::DiffuseMaterial(const DoubleVec3D& albedo = DoubleVec3D(0.0), DoubleVec3D emittance = 0)
    \brief Default and main constructor.
    \param albedo The albedo of this material.
    \param emittance The radiance this material emits.

    \fn DiffuseMaterial::DiffuseMaterial(const DiffuseMaterial& material)
    \brief Copy constructor.
    \param material The material that will be copied.

    \fn DoubleVec3D DiffuseMaterial::getAlbedo()
    \brief Getter for the albedo attribute.
    \return The albedo of this material.
    \sa setAlbedo()

    \fn void DiffuseMaterial::setAlbedo(const DoubleVec3D& albedo)
    \brief Getter for the albedo attribute.
    \param albedo The new albedo of this material.
    \sa getAlbedo()

    \fn Material* DiffuseMaterial::deepCopy()
    \brief Makes a deep copy of this material.
    \return A pointer to a deeply copied version of this material.

    \fn DoubleUnitVec3D DiffuseMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal)
    \brief Computes the new ray direction.
    \param previousRay The ray that hits this material.
    \param normal The normal at the intersection.
    \return The new ray direction.

    \fn DoubleVec3D DiffuseMaterial::computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double cosAngleNewDirectionNormal, bool nextEventEstimation = false)
    \brief Computes the new radiance.
    \param recursiveRadiance The radiance recursively obtained.
    \param cosAngleNewDirectionNormal The cosine of the angle between the direction of the next ray and the normal at the intersection.
    \param nextEventEstimation Whether the radiance is obtained using the next event estimation algorithm.
    \return The new radiance.

    \fn bool DiffuseMaterial::worksWithNextEventEstimation()
    \brief Returns whether this material works with next event estimation.
    \return True.

    \fn std::ostream& DiffuseMaterial::getDescription(std::ostream& stream)
    \brief Returns this material's description.
    \param stream The current stream.
    \return The stream with the description.
    \sa operator<<(std::ostream& stream, const Material& material)

    \fn std::string DiffuseMaterial::getType()
    \brief Returns "Diffuse".
    \return "Diffuse".

    \fn json DiffuseMaterial::getSpecificParametersJson()
    \brief Converts this material's specific parameters to json.
    \return This material's specific parameters converted to json.
    \sa DiffuseMaterial::setSpecificParametersJson()

    \fn void DiffuseMaterial::setSpecificParametersJson(const json& j)
    \brief Sets this material's specific parameters according to json.
    \param j The json input.
    \sa DiffuseMaterial::getSpecificParametersJson()
*/


class DiffuseMaterial : public Material {
private:
    DoubleVec3D albedo;

public:
    DiffuseMaterial(const DoubleVec3D& albedo = DoubleVec3D(0.0), DoubleVec3D emittance = 0);
    DiffuseMaterial(const DiffuseMaterial& material);

    DoubleVec3D getAlbedo() const;
    void setAlbedo(const DoubleVec3D& albedo);

    Material* deepCopy() const;

    DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal) const;
    DoubleVec3D computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double cosAngleNewDirectionNormal, bool nextEventEstimation = false) const;
    bool worksWithNextEventEstimation() const;

    std::ostream& getDescription(std::ostream& stream) const;
    std::string getType() const;
    json getSpecificParametersJson() const;
    void setSpecificParametersJson(const json& j);
};


#endif