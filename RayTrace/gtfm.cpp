#include "gtfm.hpp"

// Constructor / destructor.
RT::GTform::GTform()
{
  /* Set forward and backward transforms to
          identity matrices. */
  m_fwdtfm.SetToIdentity();
  m_bcktfm.SetToIdentity();
}

RT::GTform::~GTform() {}

// Construct from three vectors.
RT::GTform::GTform(const qbVector<double>& translation,
                   const qbVector<double>& rotation,
                   const qbVector<double>& scale)
{
  SetTransform(translation, rotation, scale);
}

// Construct from a pair of matrices.
RT::GTform::GTform(const qbMatrix2<double>& fwd, const qbMatrix2<double>& bck)
{
  // Verify that the inputs are 4x4.
  if ((fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) ||
      (bck.GetNumRows() != 4) || (bck.GetNumCols() != 4))
  {
    throw std::invalid_argument(
        "Cannot construct GTform, inputs are not all 4x4.");
  }

  m_fwdtfm = fwd;
  m_bcktfm = bck;
}

// Function to set the transform.
void RT::GTform::SetTransform(const qbVector<double>& translation,
                              const qbVector<double>& rotation,
                              const qbVector<double>& scale)
{
  // Define a matrix for each component of the transform.
  qbMatrix2<double> translationMatrix{4, 4};
  qbMatrix2<double> rotationMatrixX{4, 4};
  qbMatrix2<double> rotationMatrixY{4, 4};
  qbMatrix2<double> rotationMatrixZ{4, 4};
  qbMatrix2<double> scaleMatrix{4, 4};

  // Set these to identity.
  translationMatrix.SetToIdentity();
  rotationMatrixX.SetToIdentity();
  rotationMatrixY.SetToIdentity();
  rotationMatrixZ.SetToIdentity();
  scaleMatrix.SetToIdentity();

  // Populate these with the appropriate values.
  // First the translation matrix.
  translationMatrix.SetElement(0, 3, translation.GetElement(0));
  translationMatrix.SetElement(1, 3, translation.GetElement(1));
  translationMatrix.SetElement(2, 3, translation.GetElement(2));

  // Rotation matrices.
  rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
  rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
  rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
  rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

  rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
  rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
  rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
  rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

  rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
  rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
  rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
  rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));

  // And the scale matrix.
  scaleMatrix.SetElement(0, 0, scale.GetElement(0));
  scaleMatrix.SetElement(1, 1, scale.GetElement(1));
  scaleMatrix.SetElement(2, 2, scale.GetElement(2));

  // Combine to give the final forward transform matrix.
  m_fwdtfm = translationMatrix * rotationMatrixX * rotationMatrixY *
             rotationMatrixZ * scaleMatrix;

  // Compute the backwards transform.
  m_bcktfm = m_fwdtfm;
  m_bcktfm.Inverse();
}

// Functions to return the transform matrices.
qbMatrix2<double> RT::GTform::GetForward() { return m_fwdtfm; }
qbMatrix2<double> RT::GTform::GetBackward() { return m_bcktfm; }

// Function to apply the transform.
RT::Ray RT::GTform::Apply(const RT::Ray& inputRay, bool dirFlag)
{
  // Create an output object.
  RT::Ray outputRay;

  if (dirFlag)
  {
    // Apply the forward transform.
    outputRay.m_point1 = this->Apply(inputRay.m_point1, RT::FWDTFORM);
    outputRay.m_point2 = this->Apply(inputRay.m_point2, RT::FWDTFORM);
    outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
  }
  else
  {
    // Apply the backward transform.
    outputRay.m_point1 = this->Apply(inputRay.m_point1, RT::BCKTFORM);
    outputRay.m_point2 = this->Apply(inputRay.m_point2, RT::BCKTFORM);
    outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
  }

  return outputRay;
}

qbVector<double> RT::GTform::Apply(const qbVector<double>& inputVector,
                                   bool dirFlag)
{
  // Convert inputVector to a 4-element vector.
  std::vector<double> tempData{inputVector.GetElement(0),
                               inputVector.GetElement(1),
                               inputVector.GetElement(2), 1.0};
  qbVector<double> tempVector{tempData};

  // Create a vector for the result.
  qbVector<double> resultVector;

  if (dirFlag)
  {
    // Apply the forward transform.
    resultVector = m_fwdtfm * tempVector;
  }
  else
  {
    // Apply the backward transform.
    resultVector = m_bcktfm * tempVector;
  }

  // Reform the output as a 3-element vector.
  qbVector<double> outputVector{std::vector<double>{
      resultVector.GetElement(0), resultVector.GetElement(1),
      resultVector.GetElement(2)}};

  return outputVector;
}

// Overload operators.
namespace RT
{
RT::GTform operator*(const RT::GTform& lhs, const RT::GTform& rhs)
{
  // Form the product of the two forward transforms.
  qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;

  // Compute the backward transform as the inverse of the forward transform.
  qbMatrix2<double> bckResult = fwdResult;
  bckResult.Inverse();

  // Form the final result.
  RT::GTform finalResult(fwdResult, bckResult);

  return finalResult;
}
} // namespace RT

// Overload the assignment operator.
RT::GTform RT::GTform::operator=(const RT::GTform& rhs)
{
  // Make sure that we're not assigning to ourself.
  if (this != &rhs)
  {
    m_fwdtfm = rhs.m_fwdtfm;
    m_bcktfm = rhs.m_bcktfm;
  }

  return *this;
}

// Function to print the transform matrix to STDOUT.
void RT::GTform::PrintMatrix(bool dirFlag)
{
  if (dirFlag)
  {
    Print(m_fwdtfm);
  }
  else
  {
    Print(m_bcktfm);
  }
}

void RT::GTform::Print(const qbMatrix2<double>& matrix)
{
  int nRows = matrix.GetNumRows();
  int nCols = matrix.GetNumCols();
  for (int row = 0; row < nRows; ++row)
  {
    for (int col = 0; col < nCols; ++col)
    {
      std::cout << std::fixed << std::setprecision(3)
                << matrix.GetElement(row, col) << " ";
    }
    std::cout << std::endl;
  }
}

// Function to print vectors.
void RT::GTform::PrintVector(const qbVector<double>& inputVector)
{
  int nRows = inputVector.GetNumDims();
  for (int row = 0; row < nRows; ++row)
  {
    std::cout << std::fixed << std::setprecision(3)
              << inputVector.GetElement(row) << std::endl;
  }
}
