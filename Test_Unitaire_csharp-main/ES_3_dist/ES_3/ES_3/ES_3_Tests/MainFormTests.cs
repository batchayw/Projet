namespace ES_3.Tests
{
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    // Classe de tests unitaires pour la fonction MainFrom.CalculerTaxeFoncière()
    [TestClass]
    public class MainFormTests
    {
        private const float epsilon = 0.005f;         // pour comparer les résultats au sou près
        private MainForm mainForm = new MainForm();   // instance à utiliser pour les tests unitaires

        // Test unitaire #1: résidence principale, valeur foncière = 0.00$, taxation de 1.4%,
        // obtenue par BVA
        [TestMethod]
        public void CalculerTaxeFoncière_Test_01()
        {
            MainForm.CatégoriePropriété catégorie = MainForm.CatégoriePropriété.RésidencePrincipale;
            double valeurFoncière = 0.00F;

            double attendue = 0.00F;
            double obtenue = mainForm.CalculerTaxeFoncière(catégorie, valeurFoncière);

            // On s'assure d'avoir obtenu le résultat attendu
            Assert.AreEqual(attendue, obtenue, epsilon);
        }

        // Test unitaire #2: résidence principale, valeur foncière = -100.00$, invalide
        // obtenue par EP
        [TestMethod]
        [ExpectedException(typeof(System.ArgumentException))]
        public void CalculerTaxeFoncière_Test_02()
        {
            MainForm.CatégoriePropriété catégorie = MainForm.CatégoriePropriété.RésidencePrincipale;
            double valeurFoncière = -100.00F;

            // aucun résultat attendu puisqu'une exception doit être lancée
            double obtenue = mainForm.CalculerTaxeFoncière(catégorie, valeurFoncière);

            Assert.Fail();      // si l'éxécution atteint cette ligne, le test a échoué
        }

        // Test unitaire #2: résidence principale, valeur foncière = -100.00$, invalide
        // obtenue par EP
        [TestMethod]
        [ExpectedException(typeof(System.ArgumentException))]
        public void CalculerTaxeFoncière_Test_03()
        {
            MainForm.CatégoriePropriété catégorie = (MainForm.CatégoriePropriété)100;
            double valeurFoncière = 150000.00F;

            // aucun résultat attendu puisqu'une exception doit être lancée
            double obtenue = mainForm.CalculerTaxeFoncière(catégorie, valeurFoncière);

            Assert.Fail();      // si l'éxécution atteint cette ligne, le test a échoué
        }
    }
}