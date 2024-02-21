//-----------------------------------------------------------------------
// <copyright file="Program.cs" company="PlaceholderCompany">
// Copyright (c) PlaceholderCompany. All rights reserved.
// </copyright>
//-----------------------------------------------------------------------

namespace ES_3
{
    using System.Windows.Forms;

    /// <summary>
    /// Classe de la forme principale.
    /// </summary>
    public static class Program
    {
        // Point d'entrée principal de l'application
        private static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}