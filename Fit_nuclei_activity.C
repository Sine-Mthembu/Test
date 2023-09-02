#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>

// Model function for fitting
Double_t decayModel(Double_t *x, Double_t *par) {
    Double_t time = x[0];
    Double_t N0 = par[0];
    Double_t lambda_A = par[1];
    Double_t lambda_B = par[2];
    
    return N0 * exp(-lambda_A * time) * exp(-lambda_B * time);
}

int main() {
    // Create a TGraph to hold the data (time vs. activity of nuclei C)
    TGraph *dataGraph = new TGraph("data.txt"); // Load data from a file

    // Create a TF1 function for fitting
    TF1 *fitFunc = new TF1("fitFunc", decayModel, xmin, xmax, 3); // Three parameters

    // Set initial values for the fit parameters
    fitFunc->SetParameter(0, initial_N0_guess);
    fitFunc->SetParameter(1, initial_lambda_A_guess);
    fitFunc->SetParameter(2, initial_lambda_B_guess);

    // Perform the fit
    dataGraph->Fit("fitFunc", "R"); // "R" option for fitting within a specified range

    // Retrieve fit results
    Double_t N0_fit = fitFunc->GetParameter(0);
    Double_t lambda_A_fit = fitFunc->GetParameter(1);
    Double_t lambda_B_fit = fitFunc->GetParameter(2);

    // Print fit results
    std::cout << "Fit results:" << std::endl;
    std::cout << "Initial activity of nuclei C (N0): " << N0_fit << std::endl;
    std::cout << "Decay constant for A to B (lambda_A): " << lambda_A_fit << std::endl;
    std::cout << "Decay constant for B to C (lambda_B): " << lambda_B_fit << std::endl;

    // Plot the fit
    TCanvas *canvas = new TCanvas("canvas", "Decay Chain Fit", 800, 600);
    dataGraph->Draw("AP"); // "A" for points, "P" for the fit function
    fitFunc->Draw("same");
    canvas->Update();

    return 0;
}
