using System;

namespace ES_3
{
    public class Program
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
        public static double CalculerTaxeFoncière(CatégoriePropriété catégorie, double valeurFoncière)
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

        // Programme principale affichant la taxe foncière d'une propriété, calculée en 
        // fonction de sa catégorie et sa valeur foncière.
        //   args: Arguments de ligne de commande
        public static void Main(string[] args)
        {
            // Obtenir la catégorie de propriété
            int choix = 0;
            string input = string.Empty;
            do {
                Console.WriteLine("\nCatégorie de propriété:");
                Console.WriteLine("  1 - Résidence principale");
                Console.WriteLine("  2 - Résidence secondaire");
                Console.WriteLine("  3 - Terrain commercial");
                Console.WriteLine("  4 - Édifice commercial");
                Console.Write("Choix [1 à 4] ? ");

                input = Console.ReadLine();
            } while (!int.TryParse(input, out choix));

            // Obtenir la valeur foncière de la propriéeé
            double valeurFoncière = 0.0;
            do
            {
                Console.Write("\nValeur foncière de la propriété ? ");
                input = Console.ReadLine();
            } while (!double.TryParse(input, out valeurFoncière));

            // Calculer et afficher la taxe foncière de la propriété
            CatégoriePropriété catégorie = (CatégoriePropriété)(choix - 1);
            try
            {
                double taxeFoncière = Program.CalculerTaxeFoncière(catégorie, valeurFoncière);

                decimal taxe = Convert.ToDecimal(taxeFoncière);
                Console.WriteLine("Valeur foncière = " + taxe.ToString("C"));
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Valeur foncière et/ou catégorie de propriété invalide(s).");
            }
            catch (System.ArgumentException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
