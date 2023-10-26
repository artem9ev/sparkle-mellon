public class Stats  {
    private int strength = 0;
    private int agility = 0;
    private int intellegence = 0;
    Stats(int strength, int agility, int intellegence){
        this.strength = strength;
        this.agility = agility;
        this.intellegence = intellegence;
    }
    public int getStrength() {
        return strength;
    }
    public int getAgility() {
        return agility;
    }
    public int getIntellegence() {
        return intellegence;
    }

    public void addStrength(int x) throws IncorrectStatsChange {
        if (x < 0)
            throw new IncorrectStatsChange("добавляемое значение силы < 0");
        this.strength += x;
    }

    public void addAgility(int x) throws IncorrectStatsChange {
        if (x < 0)
            throw new IncorrectStatsChange("добавляемое значение ловкости < 0");
        this.agility += x;
    }
    public void addIntellegence(int x) throws IncorrectStatsChange {
        if (x < 0)
            throw new IncorrectStatsChange("добавляемое значение интелекта < 0");
        this.intellegence += x;
    }
}
