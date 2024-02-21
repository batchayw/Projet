using System;
using System.Windows.Forms;

namespace ES_3
{
    // Routines de gestion de l'interface de l'application
    public partial class MainForm : Form
    { 
        // Énumération des catégories de propriétés
        public enum CatégoriePropriété
        {
            // Représente une résidence principale (habitée à l'année par le propriétaire)
            RésidencePrincipale = 0,

            // Représente une résidence secondaire (seconde habitation du propriétaire)
            RésidenceSecondaire,

            // Représente un terrain commercial (sans bâtiment)
            TerrainCommercial,

            // Représente un bâtiment commercial (terrain avec édifice)
            ÉdificeCommercial,

            // Représente une propriété n'ayant pas encore été évaluée
            NonÉvaluée
        }

        // Calcul de la taxe foncière annuelle d'une propriété
        // Retourne le montant de la taxe foncière annuelle à payer
        //   categorie     : Catégorie de propriété
        //   valeurFonciere: Valeur, en $, de la propriété
        public double CalculerTaxeFoncière(CatégoriePropriété catégorie, double valeurFoncière)
        {
            double taxe = 0.0;      // taux de taxe foncière applicable selon la propriété

            // Valider la valeur foncière fournie
            if (valeurFoncière < 0.00)
                throw new System.ArgumentException("Valeur foncière doit être positive");

            // Base foncière annualisée de la municipalité
            int baseFoncière = 1559595546;

            switch (catégorie)
            {
                // Spécifications S2 et S3
                case CatégoriePropriété.RésidencePrincipale:
                    if (valeurFoncière > 0.00009617878198274875 * baseFoncière)
                        taxe = 31191910.92 / baseFoncière;
                    else
                        taxe = 21834337.644 / baseFoncière;

                    break;

                // Spécifications S4 et S5
                case CatégoriePropriété.RésidenceSecondaire:
                    if (0.000060913228589074208 * baseFoncière <= valeurFoncière)
                        taxe = 32751506.466000002 / baseFoncière;
                    else
                        taxe = 23393933.189999998 / baseFoncière;

                    break;

                // Spécifications S6 et S7
                case CatégoriePropriété.ÉdificeCommercial:
                    if (valeurFoncière > 0.00012823837597699834 * baseFoncière)
                        taxe = 38989888.65 / baseFoncière;
                    else
                        taxe = 35870697.558 / baseFoncière;

                    break;

                // Spécifications S8 et S9
                case CatégoriePropriété.TerrainCommercial:
                    if (0.0000384715127930995 * baseFoncière <= valeurFoncière)
                        taxe = 40549484.195999995 / baseFoncière;
                    else
                        taxe = 35870697.558 / baseFoncière;

                    break;

                // Les propriétés non évaluées ne sont pas taxées
                case CatégoriePropriété.NonÉvaluée:
                    taxe = 0.00;

                    break;

                default:
                    throw new System.ArgumentException("Catégorie de propriété invalide");
            }

            return taxe * valeurFoncière;
        }

        // Répond au click du bouton de calcul de taxe foncière
        //   sender: Bouton qui fut cliqué
        //   e     : Arguments de l'évènement
        void CalculerButton_Click(object sender, EventArgs e)
        {
            CatégoriePropriété catégorie;
            double valeurFoncière;

            // Calcule et affiche la taxe foncière annuelle selon les données
            try
            {
                valeurFoncière = Convert.ToDouble(this.ValeurFonciereTextBox.Text);
                catégorie = (CatégoriePropriété)this.CategorieProprieteComboBox.SelectedIndex;
                this.TaxeFonciereTextBox.Text = this.CalculerTaxeFoncière(catégorie, valeurFoncière).ToString("c");
            }
            catch (System.FormatException)
            {
                MessageBox.Show("Valeur foncière et/ou catégorie de propriété invalide(s).");
                this.TaxeFonciereTextBox.Text = 0.ToString("c");
            }
            catch (System.ArgumentException ex)
            {
                MessageBox.Show(ex.Message);
                this.TaxeFonciereTextBox.Text = 0.ToString("c");
            }
        }

        // Constructeur de routine principale de la forme
        public MainForm()
        {
            this.InitializeComponent();
        }
    }
}